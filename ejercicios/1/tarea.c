#include "tarea.h"
#include <string.h>

struct tarea{
	uint32_t     id;
	const char   *nombre_tarea;
	const char   *desc_tarea;
	const char   *usuario;
	uint16_t     prioridad;

	uint32_t     flags;
};

struct tarea *curso_tarea_alloc(void)
{
	return (struct tarea *)malloc(sizeof(struct tarea));
}

void curso_tarea_free(struct tarea *t)
{
	if (t->flags & (1 << CURSO_TAREA_ATTR_NOMBRE_TAREA))
		xfree(t->nombre_tarea);

	if (t->flags & (1 << CURSO_TAREA_ATTR_DESC_TAREA))
		xfree(t->desc_tarea);

	if (t->flags & (1 << CURSO_TAREA_ATTR_USUARIO))
		xfree(t->usuario);

	xfree(t);
}

bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr)
{
	return t->flags & (1 << attr);
}

void curso_tarea_attr_unset(struct tarea *t, uint16_t attr)
{
	if (!(t->flags & (1 << attr)))
		return;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (t->nombre_tarea) {
			xfree(t->nombre_tarea);
			t->nombre_tarea = NULL;
		}
		break;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (t->desc_tarea) {
			xfree(t->desc_tarea);
			t->desc_tarea = NULL;
		}
	case CURSO_TAREA_ATTR_USUARIO:
		if (t->usuario) {
			xfree(t->usuario);
			t->usuario = NULL;
		}
	case CURSO_TAREA_ATTR_ID:
		break;
	case CURSO_TAREA_ATTR_PRIORIDAD:
		break;
	}

	t->flags &= ~(1 << attr);
}

void curso_tarea_set_data(struct tarea *t, uint16_t attr, const void *data,
                          uint16_t data_len)
{
	if (attr > CURSO_TAREA_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		if (t->nombre_tarea)
			xfree(t->nombre_tarea);
		t->nombre_tarea = strdup(data);
		break;

	case CURSO_TAREA_ATTR_DESC_TAREA:
		if (t->desc_tarea)
			xfree(t->desc_tarea);
		t->desc_tarea = strdup(data);
		break;

	case CURSO_TAREA_ATTR_USUARIO:
		if (t->usuario)
			xfree(t->usuario);
		t->usuario = strdup(data);
		break;

	case CURSO_TAREA_ATTR_ID:
		t->id = *((uint32_t *)data);
		break;

	case CURSO_TAREA_ATTR_PRIORIDAD:
		t->prioridad = *((uint16_t *)data);
		break;
	}

	t->flags |= (1 << attr);
}


void curso_tarea_attr_set_u32(struct tarea *t, uint16_t attr, uint32_t data)
{
	curso_tarea_set_data(t, attr, &data, sizeof(uint32_t));
}

void curso_tarea_attr_set_u16(struct tarea *t, uint16_t attr, uint32_t data)
{
	curso_tarea_set_data(t, attr, &data, sizeof(uint16_t));
}

void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr, const char *data)
{
	curso_tarea_set_data(t, attr, data, 0);
}

const void *curso_tarea_attr_get_data(struct tarea *t, uint16_t attr)
{
	if (!(t->flags & (1 << attr)))
		return NULL;

	switch (attr) {
	case CURSO_TAREA_ATTR_NOMBRE_TAREA:
		return t->nombre_tarea;
	case CURSO_TAREA_ATTR_DESC_TAREA:
		return t->desc_tarea;
	case CURSO_TAREA_ATTR_USUARIO:
		return t->usuario;
	case CURSO_TAREA_ATTR_ID:
		return &(t->id);
	case CURSO_TAREA_ATTR_PRIORIDAD:
		return &(t->prioridad);
	}

	return NULL;
}

uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr)
{
	const char *ret = curso_tarea_attr_get_data(t, attr);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

uint16_t curso_tarea_attr_get_u16(struct tarea *t, uint16_t attr)
{
	const char *ret = curso_tarea_attr_get_data(t, attr);
	return ret == NULL ? 0 : *((uint16_t *)ret);
}

const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr)
{
	return (char *)curso_tarea_attr_get_data(t, attr);
}

int curso_tarea_snprintf(char *buf, size_t size, struct tarea *t)
{
	return snprintf(buf, size, "\nLa tarea número %d está enviada por %s." \
			"\nSe llama %s y la descripción es %s. " \
			"\nCon prioridad %d \n",
			t->id, t->usuario, t->nombre_tarea, t->desc_tarea,
			t->prioridad
                       );
}

