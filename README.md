# Ableton Programming Task - Follow Me

## Compilation

Development and testing was done in a **Docker** container running `ubuntu 18.04` with `gcc v7.3`.

To compile and run the `app` and `test` open a shell in the project root and run

	# build and run the app
	g++ -o follow_me follow_me_app.cpp src/*.cpp  -I. -Wall
	follow_me < [input_file]

	# build and run the test
	g++ -o test tests/test.cpp src/*.cpp -I. -Wall
	./test

To use the dockerized build environment and the provided `Makefile` open a shell in the project root and run:

	docker-compose build
	docker-compose run dev_env

	# build and run app
	make follow_me
	./follow_me < [input_file]

	# build and run the test
	make test
	./test

## Testing

The framework **Catch** (`v2.7.1`) has been used for tests.

In the `tests` folder there are files with test input and expected output which can used with the app.
