@echo off
del /q Log.txt
rd /s /q x64\Debug
rd /s /q x64\Release
rd /s /q .vs\LibTest\v17