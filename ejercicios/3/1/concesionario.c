#include "concesionario.h"
#include <string.h>

#define TAM_GARAJE 50

struct concesionario {
	struct coche	*garaje[TAM_GARAJE];
	const char      *dueno;
	uint32_t	num_coches;

	uint32_t	flags;
};

struct concesionario *curso_concesionario_alloc(void)
{
	return (struct concesionario *)malloc(sizeof(struct concesionario));
}

void curso_concesionario_free(struct concesionario *con)
{
	int i;

	if (con->flags & (1 << CURSO_CONCESIONARIO_ATTR_DUENO))
		xfree(con->dueno);

	for (i = 0; i < con->num_coches; i++)
		curso_coche_free(con->garaje[i]);

	xfree(con);
}

void curso_concesionario_attr_unset_coche(struct concesionario *con,
					  uint32_t pos)
{
	int i;

	if (pos < 0 || pos > con->num_coches)
		return;

	con->num_coches--;
	curso_coche_free(con->garaje[pos]);

	for (i = pos; i < con->num_coches; i++)
		con->garaje[i] = con->garaje[i+1];

}

static void curso_concesionario_set_data(struct concesionario *con,
					 uint16_t attr, const void *data)
{
	if (attr > CURSO_CONCESIONARIO_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_CONCESIONARIO_ATTR_DUENO:
		if (con->dueno)
			xfree(con->dueno);

		con->dueno = strdup(data);
		break;
	case CURSO_CONCESIONARIO_ATTR_COCHE:
		if (con->num_coches > TAM_GARAJE) {
			printf("El garaje esta lleno\n");
			break;
		}

		con->garaje[con->num_coches] = (struct coche *)data;
		con->num_coches++;
		break;
	}

	con->flags |= (1 << attr);
}

void curso_concesionario_attr_set_str(struct concesionario *con,
					uint16_t attr, const char *data)
{
	curso_concesionario_set_data(con, attr, data);
}

void curso_concesionario_attr_set_coche(struct concesionario *con,
					  uint16_t attr, struct coche *data)
{
	curso_concesionario_set_data(con, attr, data);
}

const void *curso_concesionario_attr_get_data(struct concesionario *con,
					      uint16_t attr, uint32_t pos)
{
	if (!(con->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_CONCESIONARIO_ATTR_DUENO:
		return con->dueno;
	case CURSO_CONCESIONARIO_ATTR_NUM_COCHES:
		return &con->num_coches;
	case CURSO_CONCESIONARIO_ATTR_COCHE:
		return con->garaje[pos];
	}
	return NULL;
}

uint32_t curso_concesionario_attr_get_u32(struct concesionario *con,
					  uint16_t attr)
{
	const void *ret = curso_concesionario_attr_get_data(con, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}

const char *curso_concesionario_attr_get_str(struct concesionario *con,
					     uint16_t attr)
{
	return curso_concesionario_attr_get_data(con, attr, 0);
}

struct coche *curso_concesionario_attr_get_coche(struct concesionario *con,
					         uint16_t attr, uint32_t pos)
{
	return (struct coche *)curso_concesionario_attr_get_data(con, attr,
								 pos);
}

int curso_concesionario_snprintf(char *buf, size_t size,
				 struct concesionario *con)
{
	int i, ret = 0;

	ret += snprintf(buf, size,
			"el concesionario propiedad de %s, tiene %d y son:\n",
			con->dueno, con->num_coches);

	for (i = 0; i < con->num_coches; i++) {
		ret += curso_coche_snprintf(buf + ret, size - ret, con->garaje[i]);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
