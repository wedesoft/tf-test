#include <stdio.h>
#include <ClearSilver.h>

NEOERR *out(void *ctx, char *text)
{
  fprintf((FILE *)ctx, "%s", text);
  return NULL;
}

int main(void)
{
  HDF *hdf;
  hdf_init(&hdf);
  hdf_set_value(hdf, "Op.Square.input_arg.x", "T");
  hdf_set_value(hdf, "Op.Square.output_arg.y", "T");
  hdf_set_value(hdf, "Op.Add.input_arg.x", "T");
  hdf_set_value(hdf, "Op.Add.input_arg.y", "T");
  hdf_set_value(hdf, "Op.Add.output_arg.z", "T");

  CSPARSE *parse;
  cs_init(&parse, hdf);
  cs_parse_file(parse, "test.tpl");
  cs_render(parse, stdout, out);

  cs_destroy(&parse);
  hdf_destroy(&hdf);
  return 0;
}
