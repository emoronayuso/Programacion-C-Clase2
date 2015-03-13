#include "coche.h"

int main(void)
{
	struct coche *c1;
	char info[250];

	c1 = curso_coche_alloc();

	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MATRICULA, "DF 67838 SE");
	curso_coche_attr_set_str(c1, CURSO_COCHE_ATTR_MARCA, "mini");
	curso_coche_attr_set_u32(c1, CURSO_COCHE_ATTR_ID, 0);

	curso_coche_snprintf(info, sizeof(info), c1);
	printf("los valores del coche son %s\n", info);

	curso_coche_free(c1);
	return 0;
}
