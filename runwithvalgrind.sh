echo "valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./21sh -u \n";
make run;
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./21sh -u;
