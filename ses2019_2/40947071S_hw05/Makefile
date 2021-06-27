all:
	@echo  於作業三請先安裝cJSON的lib 以免編譯不過
	@echo  網址：https://github.com/DaveGamble/cJSON#building
	@echo 
	gcc hw0501.c -o hw0501
	gcc hw0502.c -o hw0502
	gcc hw0503.c -o hw0503 -lcurl -lcjson
	@gcc test.c -o test -I /usr/local/ssl/include -L /usr/local/ssl/lib -lssl -lcrypto -Wall

clean:
	rm -rf hw0501
	rm -rf hw0502
	rm -rf hw0503
	@rm -rf test
