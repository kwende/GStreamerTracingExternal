#include <gst/gst.h>
#include "latency.h"
#include <stdio.h>

guint64 src_ts = 0, sink_ts = 0;

static void do_pull (Latency * self, guint64 ts, GstElement * element)
{
  if(element && GST_IS_OBJECT(element))
  {
    char* name = gst_element_get_name(element); 
    if(name && strcmp(name, "sink") == 0)
    {
      printf("%s at %llu\n", name, ts);
      sink_ts = ts; 
    }
  }
}

static void do_push (Latency * self, guint64 ts, GstElement * element)
{
  if(element && GST_IS_OBJECT(element))
  {
    char* name = gst_element_get_name(element); 
    if(name && strcmp(name, "src")==0)
    {
      printf("%s at %llu\n",name, ts);
      src_ts = ts; 
    }
  }
}

int main (int argc, char *argv[])
{
  GstElement *pipeline;
  GstBus *bus;
  GstMessage *msg;

  /* Initialize GStreamer */
  gst_init (&argc, &argv);

  Latency* latency = latency_new();

  //https://github.com/GStreamer/gstreamer/blob/master/plugins/tracers/gstlatency.c
  gst_tracing_register_hook (GST_TRACER (latency), "pad-push",
      G_CALLBACK (do_push));
  gst_tracing_register_hook (GST_TRACER (latency), "pad-pull-range",
      G_CALLBACK (do_pull));

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