echo "valgrind --leak-check=full --track-origins=yes ./42sh -u \n";
make run;
valgrind --leak-check=full --track-origins=yes ./42sh -up;
