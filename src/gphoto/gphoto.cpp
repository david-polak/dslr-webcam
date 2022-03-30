#include "gphoto.h"

#include <QPair>
#include <gphoto2/gphoto2-list.h>
#include <gphoto2/gphoto2-port-info-list.h>

int autodetect(CameraList *list, GPContext *context) {
  gp_raise(gp_list_reset(list));
  return gp_raise(gp_camera_autodetect(list, context));
}

QList<QPair<QString, QString>> GPhoto::getCameraList(GPContext *context) {
  QList<QPair<QString, QString>> result;
  CameraList *list;
  gp_raise(gp_list_new(&list));
  autodetect(list, context);

  const char *model;
  const char *port;

  for (int i = 0; i < gp_list_count(list); i++) {
    gp_raise(gp_list_get_name(list, i, &model));
    gp_raise(gp_list_get_value(list, i, &port));
    result.append(QPair<QString, QString>(model, port));
  }

  gp_raise(gp_list_free(list));
  return result;
}

// static void
// display_widgets (GPParams *p, CameraWidget *widget, char *prefix, int
// dumpval) { 	int 	ret, n, i; 	char	*newprefix; 	const char
// *label, *name, *uselabel; 	CameraWidgetType	type;

// 	gp_widget_get_label (widget, &label);
// 	/* fprintf(stderr,"label is %s\n", label); */
// 	ret = gp_widget_get_name (widget, &name);
// 	/* fprintf(stderr,"name is %s\n", name); */
// 	gp_widget_get_type (widget, &type);

// 	if (strlen(name))
// 		uselabel = name;
// 	else
// 		uselabel = label;

// 	n = gp_widget_count_children (widget);

// 	newprefix = malloc(strlen(prefix)+1+strlen(uselabel)+1);
// 	if (!newprefix)
// 		abort();
// 	sprintf(newprefix,"%s/%s",prefix,uselabel);

// 	if ((type != GP_WIDGET_WINDOW) && (type != GP_WIDGET_SECTION)) {
// 		printf("%s\n",newprefix);
// 		if (dumpval) print_widget (p, newprefix, widget);
// 	}
// 	for (i=0; i<n; i++) {
// 		CameraWidget *child;

// 		ret = gp_widget_get_child (widget, i, &child);
// 		if (ret != GP_OK)
// 			continue;
// 		display_widgets (p, child, newprefix, dumpval);
// 	}
// 	free(newprefix);
// }
