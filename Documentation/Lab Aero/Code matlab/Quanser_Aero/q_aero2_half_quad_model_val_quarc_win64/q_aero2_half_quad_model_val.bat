
call "setup_msvc.bat"

cd .

if "%1"=="" (nmake  -f q_aero2_half_quad_model_val.mk all) else (nmake  -f q_aero2_half_quad_model_val.mk %1)
@if errorlevel 1 goto error_exit

exit /B 0

:error_exit
echo The make command returned an error of %errorlevel%
exit /B 1