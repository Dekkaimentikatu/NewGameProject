@echo off
del /q Log.txt
rd /s /q x64\Debug
rd /s /q x64\Release
rd /s /q My_project\x64
rd /s /q .vs\My_project\v17\ipch
rd /s /q .vs\My_project.slnx\v17\ipch
rd /s /q .vs\My_project.slnx\v18\ipch