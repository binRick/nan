uncrustify -c ./etc/uncrustify.cfg --replace *.c
#tests/*.c include/*.c include/*.h src/*.c
shfmt -w *.sh
find . -name "*.unc-backup*" -type f | xargs -I % unlink %
