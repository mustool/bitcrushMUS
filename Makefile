BUNDLE = lv2pftci-bitcrushMUS.lv2
INSTALL_DIR = /usr/local/lib/lv2

$(BUNDLE): manifest.ttl bitcrushMUS.ttl bitcrushMUS.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl bitcrushMUS.ttl bitcrushMUS.so $(BUNDLE)

bitcrushMUS.so: bitcrushMUS.cpp
	g++ -shared -fPIC -DPIC bitcrushMUS.cpp `pkg-config --cflags --libs lv2-plugin` -o bitcrushMUS.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) bitcrushMUS.so
