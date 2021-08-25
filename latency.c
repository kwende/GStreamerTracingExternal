#include "latency.h"
#include <stdio.h>

struct _LatencyPrivate
{
};

Latency* latency_new(void)
{
    Latency* ret = 0; 

    ret = g_object_new (TYPE_LATENCY, NULL);

    return ret; 
}

static GObject * latency_constructor (GType type, guint n_construct_properties, 
    GObjectConstructParam *construct_properties)
{
    GObject *obj;
    /* Invoke parent constructor. */
    LatencyClass *klass;
    GObjectClass *parent_class;  
    klass = LATENCY_CLASS (g_type_class_peek (TYPE_LATENCY));
    parent_class = G_OBJECT_CLASS (g_type_class_peek_parent (klass));
    obj = parent_class->constructor (type,
                                    n_construct_properties,
                                    construct_properties);

    return obj;
}

static void latency_class_init (gpointer g_class, gpointer g_class_data)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (g_class);
  LatencyClass *klass = LATENCY_CLASS (g_class);

  gobject_class->constructor = latency_constructor;
}

static void latency_instance_init (GTypeInstance *instance, gpointer g_class)
{
  Latency *self = (Latency *)instance;
  /* do stuff */
}

GType latency_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (LatencyClass),
      NULL,   /* base_init */
      NULL,   /* base_finalize */
      latency_class_init,   /* class_init */
      NULL,   /* class_finalize */
      NULL,   /* class_data */
      sizeof (Latency),
      0,      /* n_preallocs */
      latency_instance_init    /* instance_init */
    };
    type = g_type_register_static (G_TYPE_OBJECT,
                                   "LatencyType",
                                   &info, 0);
  }
  return type;
}
