.SILENT:

semaphore_example:
	gcc -o semaphore_example_output semaphore_example.c sync_lib.o
	./semaphore_example_output
	rm semaphore_example_output

barrier_example:
	gcc -o barrier_example_output barrier_example.c sync_lib.o
	./barrier_example_output
	rm barrier_example_output

rwlock_example:
	gcc -o rwlock_example_output rwlock_example.c sync_lib.o
	./rwlock_example_output
	rm rwlock_example_output

comp_sync_lib:
	gcc -c sync_lib.c
