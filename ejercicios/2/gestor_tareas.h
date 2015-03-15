#include "tarea.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum {
	CURSO_GESTOR_TAREAS_ATTR_ARRAY_TAREAS = 0,
	CURSO_GESTOR_TAREAS_ATTR_NUM_TAREAS,
	CURSO_GESTOR_TAREAS_ATTR_NOMBRE,
	__CURSO_GESTOR_TAREAS_ATTR_MAX
};

#define CURSO_GESTOR_TAREAS_ATTR_MAX (__CURSO_GESTOR_TAREAS_ATTR_MAX - 1)

struct gestor_tareas;

struct gestor_tareas *curso_gestor_tareas_alloc(void);

void curso_gestor_tareas_free(struct gestor_tareas *gt);

void curso_gestor_tareas_attr_unset(struct gestor_tareas *gt, uint16_t attr,
                                    uint32_t pos);

bool curso_gestor_tareas_attr_is_set(const struct gestor_tareas *gt,
                                     uint16_t attr);

/* Funciones get */
const void *curso_gestor_tareas_attr_get_data(struct gestor_tareas *gt,
                                        uint16_t attr, uint32_t pos);

const char *curso_gestor_tareas_attr_get_str(struct gestor_tareas *gt,
                                          uint16_t attr);

uint32_t curso_gestor_tareas_attr_get_u32(struct gestor_tareas *gt,
                                          uint16_t attr);

struct tarea *curso_gestor_tareas_attr_get_tarea(struct gestor_tareas *gt,
                                                 uint16_t attr, uint32_t pos);

/* Funciones set */
void curso_gestor_tareas_attr_set_data(struct gestor_tareas *gt, uint16_t attr,
                                void *data);

void curso_gestor_tareas_attr_set_tarea(struct gestor_tareas *gt, uint16_t attr,
                                        struct tarea *t);

void curso_gestor_tareas_attr_set_u32(struct gestor_tareas *gt, uint16_t attr,
                                      uint32_t data);

void curso_gestor_tareas_attr_set_str(struct gestor_tareas *gt, uint16_t attr,
                                      char *data);

int curso_gestor_tareas_snprintf(char *buf, size_t size,
                                 struct gestor_tareas *gt);

