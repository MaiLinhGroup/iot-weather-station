all:
	@echo "#define MY_SSID \"$(SSID)\"" >> src/main.h
	@echo "#define MY_PSWD \"$(PWD)\"" >> src/main.h
	@echo "#define MQTT_BROKER_ADDR \"$(ADDR)\"" >> src/main.h
	@echo "#endif" >> src/main.h

clean:
	@echo "Sanitizing before pushing to GitHub..."
	@echo "#ifndef MAIN_H" > src/main.h
	@echo "#define MAIN_H" >> src/main.h
	@echo "// Run make to add the remaining content" >> src/main.h