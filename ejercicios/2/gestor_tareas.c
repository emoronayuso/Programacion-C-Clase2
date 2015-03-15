#include "gestor_tareas.h"
#include <string.h>

#define TAM_TABLA_TAREAS 10

struct gestor_tareas{
	struct tarea   *tabla_tareas[TAM_TABLA_TAREAS];
	uint32_t       num_tareas;
	char           *nombre;

	uint32_t       flags;
};

struct gestor_tareas *curso_gestor_tareas_alloc(void)
{
	char * nombre_ini = "Nuevo gestor de tareas";
	struct gestor_tareas *gt;
	int i;

	gt = (struct gestor_tareas *)malloc(sizeof(struct gestor_tareas));

	/* Inicializamos las variables */
	gt->num_tareas = 0;
	gt->flags &= ~(1 << CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS);

	for (i = 0; i < TAM_TABLA_TAREAS; i++)
		gt->tabla_tareas[i] = NULL;

	gt->nombre = strdup(nombre_ini);

	return gt;
}

void curso_gestor_tareas_free(struct gestor_tareas *gt)
{
	int i;

	for (i = 0; i < gt->num_tareas; i++)
		curso_tarea_free(gt->tabla_tareas[i]);

	if (gt->flags & (1 << CURSO_GESTOR_TAREAS_ATTR_NOMBRE))
		xfree(gt->nombre);

	xfree(gt);
}

void curso_gestor_tareas_attr_unset(struct gestor_tareas *gt, uint16_t attr,
                                    uint32_t pos)
{
	int i;

	if (!(gt->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS:
		if (pos < 0 || pos > gt->num_tareas)
			return;

		curso_tarea_free(gt->tabla_tareas[pos]);

		for (i = pos; i < gt->num_tareas; i++)
			gt->tabla_tareas[i] = gt->tabla_tareas[i+1];

		gt->num_tareas--;

		/* Si hemos borrado la ultima tarea ponemos el flag a 0 */
		if (gt->num_tareas == 0)
			gt->flags &= ~(1 << attr);

		break;
	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		break;
	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		if (gt->nombre) {
			xfree(gt->nombre);
			//gt->nombre = NULL;
		}
		gt->flags &= ~(1 << attr);
		break;
	}

}

bool curso_gestor_tareas_attr_is_set(const struct gestor_tareas *gt,
                                     uint16_t attr)
{
	return gt->flags & (1 << attr);
}

/* Funciones get */
const void *curso_gestor_tareas_attr_get_data(struct gestor_tareas *gt,
                                              uint16_t attr, uint32_t pos)
{
	if (!(gt->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS:
		if (pos < 0 || pos > gt->num_tareas)
			return;
		return gt->tabla_tareas[pos];
	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		return &(gt->num_tareas);
	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		return gt->nombre;
	}
	return NULL;
}

const char *curso_gestor_tareas_attr_get_str(struct gestor_tareas *gt,
                                             uint16_t attr)
{
	return curso_gestor_tareas_attr_get_data(gt, attr, 0);
}


uint32_t curso_gestor_tareas_attr_get_u32(struct gestor_tareas *gt,
                                          uint16_t attr)
{
	const char *ret = curso_gestor_tareas_attr_get_data(gt, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

struct tarea *curso_gestor_tareas_attr_get_tarea(struct gestor_tareas *gt,
                                                 uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_tareas_attr_get_data(gt, attr, pos);
}

/* Funciones set */
void curso_gestor_tareas_attr_set_data(struct gestor_tareas *gt, uint16_t attr,
                                void *data)
{
	int pos = 0;
	int i;

	if (attr > CURSO_GESTOR_TAREAS_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS:
		if (gt->num_tareas >= TAM_TABLA_TAREAS) {
			printf("\n---La lista de tareas esta completa---\n");
			break;
		}

		/* Si es la primera tarea */
		if ( gt->num_tareas == 0)
			gt->tabla_tareas[0] = (struct tarea *)data;
		else {
			/* Si no, buscamos la posicion de la nueva tarea */
			while (pos < gt->num_tareas &&
                               curso_tarea_attr_get_u32(gt->tabla_tareas[pos],
                               CURSO_TAREA_ATTR_PRIORIDAD) <
                               curso_tarea_attr_get_u32(data,
                               CURSO_TAREA_ATTR_PRIORIDAD)
                              ) {
				pos++;
			}

			/* Colocamos la tarea en su sitio segun su prioridad */
			for (i = gt->num_tareas - 1; i >= pos; i--)
				gt->tabla_tareas[i + 1] = gt->tabla_tareas[i];

			gt->tabla_tareas[pos] = data;
		}

		/* Ponemos el flag de num_tareas a 1 */
		gt->flags |= (1 << CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS);

		gt->num_tareas++;
		break;

	case CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS:
		break;

	case CURSO_GESTOR_TAREAS_ATTR_NOMBRE:
		if (gt->nombre)
			xfree(gt->nombre);
		gt->nombre = strdup(data);
		break;
	}

	gt->flags |= (1 << attr);
}

void curso_gestor_tareas_attr_set_tarea(struct gestor_tareas *gt,
                                        uint16_t attr, struct tarea *t)
{
	curso_gestor_tareas_attr_set_data(gt, attr, t);
}

void curso_gestor_tareas_attr_set_u32(struct gestor_tareas *gt, uint16_t attr,
                                      uint32_t data)
{
	curso_gestor_tareas_attr_set_data(gt, attr, &data);
}


void curso_gestor_tareas_attr_set_str(struct gestor_tareas *gt, uint16_t attr,
                                      char *data)
{
	curso_gestor_tareas_attr_set_data(gt, attr, data);
}


/* Función que imprime todas las tareas */
int curso_gestor_tareas_snprintf(char *buf, size_t size,
                                 struct gestor_tareas *gt)
{
	int i,ret = 0;

	for (i = 0; i < gt->num_tareas; i++) {
		ret += curso_tarea_snprintf(buf + ret, size - ret,
                                            gt->tabla_tareas[i]);

		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}

