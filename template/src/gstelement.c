#include "gst{{ elementname }}.h"

GST_DEBUG_CATEGORY_STATIC (gst_{{ element_name }}_debug);
#define GST_CAT_DEFAULT gst_{{ element_name }}_debug

enum
{
  PROP_0,
  PROP_SILENT
};

/* The capabilities of the inputs and outputs. */
static GstStaticPadTemplate sink_factory = GST_STATIC_PAD_TEMPLATE ("sink",
    GST_PAD_SINK,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

static GstStaticPadTemplate src_factory = GST_STATIC_PAD_TEMPLATE ("src",
    GST_PAD_SRC,
    GST_PAD_ALWAYS,
    GST_STATIC_CAPS ("ANY")
    );

#define gst_{{ element_name }}_parent_class parent_class
G_DEFINE_TYPE (Gst{{ ElementName }}, gst_{{ element_name }}, GST_TYPE_ELEMENT);

static void gst_{{ element_name }}_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec);
static void gst_{{ element_name }}_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec);

static gboolean gst_{{ element_name }}_sink_event (GstPad * pad, GstObject * parent, GstEvent * event);
static GstFlowReturn gst_{{ element_name }}_chain (GstPad * pad, GstObject * parent, GstBuffer * buf);

/* GObject vmethod implementations */

/* Initialize the plugin's class */
static void
gst_{{ element_name }}_class_init (Gst{{ ElementName }}Class * klass)
{
  GObjectClass *gobject_class;
  GstElementClass *gstelement_class;

  gobject_class = (GObjectClass *) klass;
  gstelement_class = (GstElementClass *) klass;

  gobject_class->set_property = gst_{{ element_name }}_set_property;
  gobject_class->get_property = gst_{{ element_name }}_get_property;

  g_object_class_install_property (gobject_class, PROP_SILENT,
      g_param_spec_boolean ("silent", "Silent", "Produce verbose output ?",
          FALSE, G_PARAM_READWRITE));

  gst_element_class_set_details_simple(gstelement_class,
    "{{ elementname }}",
    "Generic/Filter",
    "{{ element_description }}",
    "{{ author }}");

  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&src_factory));
  gst_element_class_add_pad_template (gstelement_class,
      gst_static_pad_template_get (&sink_factory));
}

/* Initialize the new element
 * Instantiate pads and add them to element
 * Set pad calback functions
 * Initialize instance structure
 */
static void
gst_{{ element_name }}_init (Gst{{ ElementName }} *self)
{
  self->sinkpad = gst_pad_new_from_static_template (&sink_factory, "sink");
  gst_pad_set_event_function (self->sinkpad,
                              GST_DEBUG_FUNCPTR(gst_{{ element_name }}_sink_event));
  gst_pad_set_chain_function (self->sinkpad,
                              GST_DEBUG_FUNCPTR(gst_{{ element_name }}_chain));
  GST_PAD_SET_PROXY_CAPS (self->sinkpad);
  gst_element_add_pad (GST_ELEMENT (self), self->sinkpad);

  self->srcpad = gst_pad_new_from_static_template (&src_factory, "src");
  GST_PAD_SET_PROXY_CAPS (self->srcpad);
  gst_element_add_pad (GST_ELEMENT (self), self->srcpad);

  self->silent = FALSE;
}

static void
gst_{{ element_name }}_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  Gst{{ ElementName }} *self = GST_{{ ELEMENT_NAME }} (object);

  switch (prop_id) {
    case PROP_SILENT:
      self->silent = g_value_get_boolean (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

static void
gst_{{ element_name }}_get_property (GObject * object, guint prop_id,
    GValue * value, GParamSpec * pspec)
{
  Gst{{ ElementName }} *self = GST_{{ ELEMENT_NAME }} (object);

  switch (prop_id) {
    case PROP_SILENT:
      g_value_set_boolean (value, self->silent);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}

/* GstElement vmethod implementations */

/* This function handles sink events */
static gboolean
gst_{{ element_name }}_sink_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  Gst{{ ElementName }} *self;
  gboolean ret;

  self = GST_{{ ELEMENT_NAME }} (parent);

  GST_LOG_OBJECT (self, "Received %s event: %" GST_PTR_FORMAT,
      GST_EVENT_TYPE_NAME (event), event);

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_CAPS:
    {
      GstCaps * caps;

      gst_event_parse_caps (event, &caps);
      /* Do something with the caps */

      /* and forward */
      ret = gst_pad_event_default (pad, parent, event);
      break;
    }
    default:
      ret = gst_pad_event_default (pad, parent, event);
      break;
  }
  return ret;
}

/* Chain function
 * This function does the actual processing
 */
static GstFlowReturn
gst_{{ element_name }}_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  Gst{{ ElementName }} *self;

  self = GST_{{ ELEMENT_NAME }} (parent);

  if (self->silent == FALSE)
    GST_INFO ("I'm plugged, therefore I'm in.");

  return gst_pad_push (self->srcpad, buf);
}


/*
 * Initialize the plug-in itself
 * Register the element factories and other features
 */
static gboolean
plugin_init (GstPlugin * plugin)
{
  /* Debug category for filtering log messages */
  GST_DEBUG_CATEGORY_INIT (gst_{{ element_name }}_debug, "{{ elementname }}",
      0, "{{ element_description }}");

  return gst_element_register (plugin, "{{ elementname }}", GST_RANK_NONE,
      GST_TYPE_{{ ELEMENT_NAME }});
}

#ifndef PACKAGE
#define PACKAGE "{{ package }}"
#endif

/* GStreamer looks for this structure to register plugins */
GST_PLUGIN_DEFINE (
		GST_VERSION_MAJOR,
		GST_VERSION_MINOR,
		{{ elementname }},
		"{{ element_description }}",
		plugin_init,
		"{{ package_version }}",
		"{{ license }}",
		"{{ package_name }}",
		"{{ package_origin }}"
		)
