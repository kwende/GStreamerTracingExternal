#include <glib-object.h>
#include <gst/gst.h>

#include <gst/gsttracer.h>

//https://gtk.developpez.com/doc/en/gobject/chapter-gobject.html
//https://www.freedesktop.org/software/gstreamer-sdk/data/docs/2012.5/gobject/gobject-The-Base-Object-Type.html

#define TYPE_LATENCY (latency_get_type ())
#define LATENCY(obj)(G_TYPE_CHECK_INSTANCE_CAST ((obj), TYPE_LATENCY, Latency))
#define LATENCY_CLASS(klass)(G_TYPE_CHECK_CLASS_CAST ((klass), TYPE_LATENCY, LatencyClass))

typedef struct _Latency Latency;
typedef struct _LatencyClass LatencyClass;
typedef struct _LatencyPrivate LatencyPrivate;

struct _Latency {
  GstTracer 	 object;

  /* <private> */
  LatencyPrivate *priv;
};

struct _LatencyClass {
  GstTracerClass	parent_class;
};

Latency* latency_new(void);
GType latency_get_type(void);