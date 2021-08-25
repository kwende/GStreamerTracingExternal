#include <gst/gst.h>
#include "latency.h"
#include <stdio.h>

static void do_element_new (Latency * self, guint64 ts, GstElement * element)
{
  printf("new!\n");
}

int main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  Latency* latency = latency_new();

  gst_tracing_register_hook (GST_TRACER (latency), "element-new",
      G_CALLBACK (do_element_new));

  /* Build the pipeline */
  pipeline = gst_parse_launch("videotestsrc num-buffers=100 ! x264enc ! mp4mux ! filesink location=file.mp4", NULL);

  /* Start playing */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Wait until error or EOS */
  bus = gst_element_get_bus (pipeline);
  msg = gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
      GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

  /* Free resources */
  if (msg != NULL)
    gst_message_unref (msg);
  gst_object_unref (bus);
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (pipeline);
  return 0;
}