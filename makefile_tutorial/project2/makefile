#simple example
#1
#hello:
#	echo "Hello, World"
#

#2
#blah: blah.o
#	cc blah.o -o blah
#
#blah.o: blah.c
#	cc -c blah.c -o blah.o

#3
#some_file: other_file
#	echo "This will always run, and runs second"
#	touch some_file
#
#other_file:
#	echo "This will always run, and runs first"
#
#clean:
#	rm -f some_file
#

#Variables
#4
#files := file1 file2
#some_file: $(files)
#	echo "Look at this variable: " $(files)
#	touch some_file
#
#file1:
#	touch file1
#file2:
#	touch file2
#
#clean:
#	rm -f file1 file2 some_file
#

#5
#a := one two# a is set to the string "one two"
#b := 'one two' # Not recommended. b is set to the string "'one two'"
#all:
#	printf '$a'
#	printf $b
#

#6
#x := dude
#
#all:
#	echo $(x)
#	echo ${x}
#
#	# Bad practice, but works
#	echo $x
#

#Targets
#7
#all: one two three
#
#one:
#	touch one
#two:
#	touch two
#three:
#	touch three
#
#clean:
#	rm -f one two three
#

#8
#all: f1.o f2.o
#
#f1.o f2.o:
#	echo $@
# Equivalent to:
# f1.o:
#	 echo f1.o
# f2.o:
#	 echo f2.o

#Automatic Variables and Wildcards
#9
# Print out file information about every .c file
#print: $(wildcard *.c)
#	ls -la  $?
#
#
#10
#thing_wrong := *.o # Don't do this! '*' will not get expanded
#thing_right := $(wildcard *.o)
#
#all: one two three four
#
## Fails, because $(thing_wrong) is the string "*.o"
#one: $(thing_wrong)
#
## Stays as *.o if there are no files that match this pattern :(
#two: *.o 
#
## Works as you would expect! In this case, it does nothing.
#three: $(thing_right)
#
## Same as rule three
#four: $(wildcard *.o)

#11
#hey: one two
#	# Outputs "hey", since this is the target name
#	echo $@
#
#	# Outputs all prerequisites newer than the target
#	echo $?
#
#	# Outputs all prerequisites
#	echo $^
#
#	# Outputs the first prerequisite
#	echo $<
#
#	touch hey
#
#one:
#	touch one
#
#two:
#	touch two
#
#clean:
#	rm -f hey one two
#

#Fancy Rules
#12
#--------------------typical-----------------------
#objects = foo.o bar.o all.o
#all: $(objects)
#	$(CC) $^ -o all
#
#foo.o: foo.c
#	$(CC) -c foo.c -o foo.o
#
#bar.o: bar.c
#	$(CC) -c bar.c -o bar.o
#
#all.o: all.c
#	$(CC) -c all.c -o all.o
#
#all.c:
#	echo "int main() { return 0; }" > all.c
#
## Note: all.c does not use this rule because Make prioritizes more specific matches when there is more than one match.
#%.c:
#	touch $@
#
#clean:
#	rm -f *.c *.o all
#--------------------end---------------------------

#--------------------static-----------------------
#objects = foo.o bar.o all.o
#all: $(objects)
#	$(CC) $^ -o all
#
#$(objects): %.o: %.c
#	$(CC) -c $^ -o $@
#all.c:
#	echo "int main() { return 0; }" > all.c
#
#%.c:
#	touch $@
#clean:
#	rm -f *.c *.o all
#--------------------end---------------------------

#13
#obj_files = foo.result bar.o lose.o
#src_files = foo.raw bar.c lose.c
#
#all: $(obj_files)
## Note: PHONY is important here. Without it, implicit rules will try to build the executable "all", since the prereqs are ".o" files.
#.PHONY: all 
#
## Ex 1: .o files depend on .c files. Though we don't actually make the .o file.
#$(filter %.o,$(obj_files)): %.o: %.c
#	echo "target: $@ prereq: $<"
#
## Ex 2: .result files depend on .raw files. Though we don't actually make the .result file.
#$(filter %.result,$(obj_files)): %.result: %.raw
#	echo "target: $@ prereq: $<" 
#
#%.c %.raw:
#	touch $@
#
#clean:
#	rm -f $(src_files)
#

#commands and excution
#14
#all:
#	@echo "This make line will not be printed"
#	echo "But this will"
#

#15
#SHELL=/bin/bash
#
#cool:
#	echo "Hello from bash"
#

#16
#double dollar sign
#make_var = I am a make variable
#all:
#	# Same as running "sh_var='I am a shell variable'; echo $sh_var" in the shell
#	sh_var='I am a shell variable'; echo $$sh_var
#
#	# Same as running "echo I am a make variable" in the shell
#	echo $(make_var)
#

#17
#new_contents = "hello:\n\ttouch inside_file"
#all:
#	mkdir -p subdir
#	printf $(new_contents) | sed -e 's/^ //' > subdir/makefile
#	cd subdir && $(MAKE)
#
#clean:
#	rm -rf subdir
#

#18
# Run this with "export shell_env_var='I am an environment variable'; make"
#all:
#	# Print out the Shell variable
#	echo $$shell_env_var
#
#	# Print out the Make variable
#	echo $(shell_env_var)


#19
#shell_env_var=Shell env var, created inside of Make
#export shell_env_var
#all:
#	echo $(shell_env_var)
#	echo $$shell_env_var
#

#20
#new_contents = "hello:\n\techo \$$(cooly)"
#
#all:
#	mkdir -p subdir
#	printf $(new_contents) | sed -e 's/^ //' > subdir/makefile
#	@echo "---MAKEFILE CONTENTS---"
#	@cd subdir && cat makefile
#	@echo "\n---END MAKEFILE CONTENTS---"
#	cd subdir && $(MAKE)
#
## Note that variables and exports. They are set/affected globally.
#cooly = "The subdirectory can see me!"
#export cooly
## This would nullify the line above: unexport cooly
#
#clean:
#	rm -rf subdir
#

#21
#one=this will only work locally
#export two=we can run subcommands with this
#
#all: 
#	@echo $(one)
#	@echo $$one
#	@echo $(two)
#	@echo $$two
#

#22
#.EXPORT_ALL_VARIABLES:
#new_contents = "hello:\n\techo \$$(cooly)"
#
#cooly = "The subdirectory can see me!"
## This would nullify the line above: unexport cooly
#
#all:
#	mkdir -p subdir
#	printf $(new_contents) | sed -e 's/^ //' > subdir/makefile
#	@echo "---MAKEFILE CONTENTS---"
#	@cd subdir && cat makefile
#	@echo "\n---END MAKEFILE CONTENTS---"
#	cd subdir && $(MAKE)
#
#clean:
#	rm -rf subdir
#

#23
# Recursive variable. This will print "later" below
#one = one ${later_variable}
## Simply expanded variable. This will not print "later" below
#two := two ${later_variable}
#
#later_variable = later
#
#all: 
#	echo $(one)
#	echo $(two)

#24
#one = hello
#one ?= will not be set
#two ?= will be set
#
#all: 
#	echo $(one)
#	echo $(two)
#

#25
#with_spaces = hello   # with_spaces has many spaces after "hello"
#after = $(with_spaces)there
#
#nullstring =
#space = $(nullstring) # Make a variable with a single space.
#
#all: 
#	echo "$(after)"
#	echo start"$(space)"end
#

#26
# Overrides command line arguments
#override option_one = did_override
## Does not override command line arguments
#option_two = not_override
#all: 
#	echo $(option_one)
#	echo $(option_two)
#

#27
#each line in a seprate shell
#one = export blah="I was set!"; echo $$blah
#
#define two
#export blah="I was set!"
#echo $$blah
#endef
#
#all: 
#	@echo "This prints 'I was set'"
#	@$(one)
#	@echo "This does not print 'I was set' because each command runs in a separate shell"
#	@$(two)
#

#28
#all: one = cool
#
#all: 
#	echo one is defined: $(one)
#
#other:
#	echo one is nothing: $(one)
#

#29
#%.c: one = cool
#
#blah.c: 
#	echo one is defined: $(one)
#
#other:
#	echo one is nothing: $(one)
#

#Conditional part of Makefiles
#30
#%.c: one = cool
#
#blah.c: 
#	echo one is defined: $(one)
#
#other:
#	echo one is nothing: $(one)
#

#31
#foo = ok
#
#all:
#ifeq ($(foo), ok)
#	echo "foo equals ok"
#else
#	echo "nope"
#endif

#32
#strio will delete all space in the foo
#nullstring =
#foo = $(nullstring) # end of line; there is a space here
#
#all:
#ifeq ($(strip $(foo)),)
#	echo "foo is empty after being stripped"
#endif
#ifeq ($(nullstring),)
#	echo "nullstring doesn't even have spaces"
#endif

#33
#bar =
#foo = $(bar)
#
#all:
#ifdef foo
#	echo "foo is defined"
#endif
#ifndef bar
#	echo "but bar is not"
#endif

#34
#all:
## Search for the "-i" flag. MAKEFLAGS is just a list of single characters, one per flag. So look for "i" in this case.
#ifneq (,$(findstring i, $(MAKEFLAGS)))
#	echo "i was passed to MAKEFLAGS"
#endif

#35
bar := ${subst not,"totally", "I am not superman"}
all: 
	@echo $(bar)

