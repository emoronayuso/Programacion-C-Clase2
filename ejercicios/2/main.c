#include "gestor_tareas.h"
#include <assert.h>
#include <string.h>

int main(void)
{
	struct tarea *t1, *t2, *t3;
	struct gestor_tareas *gt;
	char buffer[4000];

	printf("\n --- Creamos 3 tareas.....\n");
	t1 = curso_tarea_alloc();
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE_TAREA,
				"Primera tarea");
	assert(0 == strcmp(curso_tarea_attr_get_str(t1,
                           CURSO_TAREA_ATTR_NOMBRE_TAREA),"Primera tarea"));

	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DESC_TAREA,
				"Esta es la descripción de la tarea 1");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO,
				"Fulanito");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 1457);
	curso_tarea_attr_set_u16(t1, CURSO_TAREA_ATTR_PRIORIDAD, 23);
	curso_tarea_snprintf(buffer, sizeof(buffer), t1);
	printf("%s", buffer);

	t2 = curso_tarea_alloc();
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_NOMBRE_TAREA,
				"Segunda tarea");
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_DESC_TAREA,
				"Esta es la descripción de la tarea 2");
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_USUARIO,
				"Benganito");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_ID, 1887);
	curso_tarea_attr_set_u16(t2, CURSO_TAREA_ATTR_PRIORIDAD, 2);
	curso_tarea_snprintf(buffer, sizeof(buffer), t2);
	printf("%s", buffer);

	t3 = curso_tarea_alloc();
	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_NOMBRE_TAREA,
				"Tercera tarea");
	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_DESC_TAREA,
				"Esta es la descripción de la tarea 3");
	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_USUARIO,
				"Bar");
	curso_tarea_attr_set_u32(t3, CURSO_TAREA_ATTR_ID, 1986);
	curso_tarea_attr_set_u16(t3, CURSO_TAREA_ATTR_PRIORIDAD, 7);
	curso_tarea_snprintf(buffer, sizeof(buffer), t3);
	printf("%s", buffer);


	printf("\n --- Creamos un gestor de tareas.....\n");
	gt = curso_gestor_tareas_alloc();

	curso_gestor_tareas_attr_set_str(gt, CURSO_GESTOR_TAREAS_ATTR_NOMBRE,
                                         "Nombre del gestor de tareas");

	assert(0 == strcmp(curso_gestor_tareas_attr_get_str(gt,
                                              CURSO_GESTOR_TAREAS_ATTR_NOMBRE),
                                              "Nombre del gestor de tareas"));

	printf("\n --- Incluimos las tareas en el gestor de tareas....\n");
	curso_gestor_tareas_attr_set_tarea(gt, 
                                          CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS,
					  t1);
	
	curso_gestor_tareas_attr_set_tarea(gt, 
                                          CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS,
					  t2);

	curso_gestor_tareas_attr_set_tarea(gt, 
                                          CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS,
					  t3);

	assert(3 == curso_gestor_tareas_attr_get_u32(gt,
                                          CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS));

	printf("\n --- Mostramos todas las tareas\n");
	curso_gestor_tareas_snprintf(buffer, sizeof(buffer), gt);
	printf("%s", buffer);

	printf("\n --- La tarea de mayor prioridad es:");
	curso_tarea_snprintf(buffer, sizeof(buffer),
                             curso_gestor_tareas_attr_get_tarea(gt,
                             CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS, 0)
                            );
	printf("%s", buffer);

	printf("\n --- Borramos la tarea de mayor prioridad\n");
	curso_gestor_tareas_attr_unset(gt, 
                                     CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS, 0);
	
	assert(2 == curso_gestor_tareas_attr_get_u32(gt,
                                          CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS));

	printf("\n --- La tarea de mayor prioridad ahora es:");
	curso_tarea_snprintf(buffer, sizeof(buffer),
                             curso_gestor_tareas_attr_get_tarea(gt,
                             CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS, 0)
                            );
	printf("%s", buffer);

	printf("\n --- Liberamos la memoria, eliminando las tareas y " \
			"el gestor de tareas ....\n");
	curso_gestor_tareas_free(gt);



}
