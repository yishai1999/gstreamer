#ifndef __GST_{{ ELEMENT_NAME }}_H__
#define __GST_{{ ELEMENT_NAME }}_H__

#include <gst/gst.h>

G_BEGIN_DECLS

#define GST_TYPE_{{ ELEMENT_NAME }} (gst_{{ element_name }}_get_type())
G_DECLARE_FINAL_TYPE (Gst{{ ElementName }}, gst_{{ element_name }},
    GST, {{ ELEMENT_NAME }}, GstElement)

struct _Gst{{ ElementName }}
{
  GstElement element;

  GstPad *sinkpad, *srcpad;

  gboolean silent;
};

G_END_DECLS

#endif /* __GST_{{ ELEMENT_NAME }}_H__ */
