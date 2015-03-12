#include "tarea.h"
#include <assert.h>
#include <string.h>

int main(void)
{
	struct tarea *t1;
	char buffer[250];

	t1 = curso_tarea_alloc();
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE_TAREA,
				"Primera tarea");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DESC_TAREA,
				"Esta es la descripción de la tarea");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO,
				"Fulanito");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 1457);
	curso_tarea_attr_set_u16(t1, CURSO_TAREA_ATTR_PRIORIDAD, 7);
	curso_tarea_snprintf(buffer, sizeof(buffer), t1);
	printf("%s", buffer);

	assert(0 == strcmp(curso_tarea_attr_get_str
                          (t1, CURSO_TAREA_ATTR_NOMBRE_TAREA),
                          "Primera tarea")
              );

	assert(1457 == curso_tarea_attr_get_u32(t1, CURSO_TAREA_ATTR_ID));

	printf("\n --- Se modifican los atributos de la tarea...\n");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, "Benganito");
	assert(0 == strcmp(curso_tarea_attr_get_str
			(t1, CURSO_TAREA_ATTR_USUARIO),
			"Benganito")
              );

	curso_tarea_attr_set_u16(t1, CURSO_TAREA_ATTR_PRIORIDAD, 45);
	assert(45 == curso_tarea_attr_get_u16(t1, CURSO_TAREA_ATTR_PRIORIDAD));

	curso_tarea_snprintf(buffer, sizeof(buffer), t1);
	printf("%s", buffer);

	printf("\n --- Se eliminan algunos atributos...\n");

	curso_tarea_attr_unset(t1, CURSO_TAREA_ATTR_DESC_TAREA);
	assert(false == curso_tarea_attr_is_set(t1, CURSO_TAREA_ATTR_DESC_TAREA)
              );

	curso_tarea_free(t1);

	return 0;
}
