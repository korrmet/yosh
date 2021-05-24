all: release

release:
	mkdir -p release

debug:
	mkdir -p debug

clean:
	rm -rf test sandbox
