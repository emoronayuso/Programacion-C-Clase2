#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	CURSO_TAREA_ATTR_NOMBRE_TAREA = 0,
	CURSO_TAREA_ATTR_DESC_TAREA,
	CURSO_TAREA_ATTR_ID,
	CURSO_TAREA_ATTR_USUARIO,
	CURSO_TAREA_ATTR_PRIORIDAD,
	__CURSO_TAREA_ATTR_MAX
};

#define CURSO_TAREA_ATTR_MAX (__CURSO_TAREA_ATTR_MAX - 1)

#define xfree(ptr)	free((void *) ptr);

struct tarea;

struct tarea *curso_tarea_alloc(void);
void curso_tarea_free(struct tarea *t);

bool curso_tarea_attr_is_set(const struct tarea *t, uint16_t attr);

void curso_tarea_attr_unset(struct tarea *t, uint16_t attr);

void curso_tarea_attr_set_data(struct tarea *t, uint16_t attr, const void *data,
                               uint16_t data_len);
void curso_tarea_attr_set_u32(struct tarea *t, uint16_t attr, uint32_t data);
void curso_tarea_attr_set_u16(struct tarea *t, uint16_t attr, uint32_t data);
void curso_tarea_attr_set_str(struct tarea *t, uint16_t attr, const char *data);

const void *curso_tarea_attr_get_data(struct tarea *t, uint16_t attr);
uint32_t curso_tarea_attr_get_u32(struct tarea *t, uint16_t attr);
uint16_t curso_tarea_attr_get_u16(struct tarea *t, uint16_t attr);
const char *curso_tarea_attr_get_str(struct tarea *t, uint16_t attr);

int curso_tarea_snprintf(char *buf, size_t size, struct tarea *t);

