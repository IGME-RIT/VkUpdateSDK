..\Bin\glslangValidator.exe -V cube.vert -o cube.vert.spv
..\Bin\glslangValidator.exe -V cube.frag -o cube.frag.spv
..\Bin\spirv-opt --strip-debug cube.vert.spv -o cube2.vert.spv
..\Bin\spirv-opt --strip-debug cube.frag.spv -o cube2.frag.spv
bin2hex --i cube2.vert.spv --o cube.vert.inc
bin2hex --i cube2.frag.spv --o cube.frag.inc
del cube.vert.spv
del cube.frag.spv
del cube2.vert.spv
del cube2.frag.spv

..\Bin\glslangValidator.exe -V sky.vert -o sky.vert.spv
..\Bin\glslangValidator.exe -V sky.frag -o sky.frag.spv
..\Bin\spirv-opt --strip-debug sky.vert.spv -o sky2.vert.spv
..\Bin\spirv-opt --strip-debug sky.frag.spv -o sky2.frag.spv
bin2hex --i sky2.vert.spv --o sky.vert.inc
bin2hex --i sky2.frag.spv --o sky.frag.inc
del sky.vert.spv
del sky.frag.spv
del sky2.vert.spv
del sky2.frag.spv

..\Bin\glslangValidator.exe -V bumpy.vert -o bumpy.vert.spv
..\Bin\glslangValidator.exe -V bumpy.frag -o bumpy.frag.spv
..\Bin\spirv-opt --strip-debug bumpy.vert.spv -o bumpy2.vert.spv
..\Bin\spirv-opt --strip-debug bumpy.frag.spv -o bumpy2.frag.spv
bin2hex --i bumpy2.vert.spv --o bumpy.vert.inc
bin2hex --i bumpy2.frag.spv --o bumpy.frag.inc
del bumpy.vert.spv
del bumpy.frag.spv
del bumpy2.vert.spv
del bumpy2.frag.spv

..\Bin\glslangValidator.exe -V sprite2D.vert -o sprite2D.vert.spv
..\Bin\glslangValidator.exe -V sprite2D.frag -o sprite2D.frag.spv
..\Bin\spirv-opt --strip-debug sprite2D.vert.spv -o sprite2D2.vert.spv
..\Bin\spirv-opt --strip-debug sprite2D.frag.spv -o sprite2D2.frag.spv
bin2hex --i sprite2D2.vert.spv --o sprite2D.vert.inc
bin2hex --i sprite2D2.frag.spv --o sprite2D.frag.inc
del sprite2D.vert.spv
del sprite2D.frag.spv
del sprite2D2.vert.spv
del sprite2D2.frag.spv

pause