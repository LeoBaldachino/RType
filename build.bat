@if not exist "external/boost" (
    @echo Updating submodules...
    @git submodule update --init --recursive
)

@echo Building Boost.Build...
@cd external/boost/
call bootstrap.bat
call b2
call b2 headers

@echo Building project...
@cd ../../
if not exist "build" mkdir build
@cd build
@echo Removing everything in build...
@rd /s /q *
@echo Building project...
@cmake ..

@echo Done building project.