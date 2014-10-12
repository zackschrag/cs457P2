#include <p2.h>
#include <reader.h>


using namespace std;

// #define NUM_THREADS 5

// struct thread_data{
//    int  thread_id;
//    char *message;
// };

// void *PrintHello(void *threadarg)
// {
//    struct thread_data *my_data;

//    my_data = (struct thread_data *) threadarg;

//    cout << "Thread ID : " << my_data->thread_id ;
//    cout << " Message : " << my_data->message << endl;

//    pthread_exit(NULL);
// }

// int main(int argc, char **argv) {
// 	Reader r(argc, argv);
// 	r.validate();
//    	pthread_t threads[NUM_THREADS];
//    	struct thread_data td[NUM_THREADS];
//    	int rc;
//    	int i;

//    	for( i=0; i < NUM_THREADS; i++ ){
//     	cout <<"main() : creating thread, " << i << endl;
//       	td[i].thread_id = i;
//       	td[i].message = "This is message";
//       	rc = pthread_create(&threads[i], NULL,
//                           PrintHello, (void *)&td[i]);
//       	if (rc){
//          	cout << "Error:unable to create thread," << rc << endl;
//          	exit(-1);
//       	}
//    	}
//    	pthread_exit(NULL);
// }

int main(int argc, char **argv) {
	Reader r(argc, argv);
	r.validate();

	// Now we know all arguments are valid
	//Parse chainfile and construct ChainData object
	cout << "r.getChainFile() -- " << r.getChainFile() << endl;
	r.parseFile(r.getChainFile());

	cout << "awget:" << endl;
	cout << "\tRequest: " << argv[1] << endl;
	ChainData cd = r.getChainData();
	cd.listEntries();

	// Initialize request to SS
	r.connectToSS();
}