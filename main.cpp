#include<stdio.h>
#include<stdlib.h>
#ifdef EMSCRIPTEN
#include<emscripten/emscripten.h>
#define GLFW_INCLUDE_ES3
#endif
#include<GLFW/glfw3.h>
#include <iostream>



#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int testSocket() {
	const char* server_name = "127.0.0.1";
	const int server_port = 65431;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	// creates binary representation of server name
	// and stores it as sin_addr
	// http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	// htons: port in network order format
	server_address.sin_port = htons(server_port);

	// open a stream socket
	int sock;
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("could not create socket %d \n", sock);
		return 1;
	}

	// TCP is connection oriented, a reliable connection
	// **must** be established before any data is exchanged
    int res = connect(sock, (struct sockaddr*)&server_address,
	            sizeof(server_address));
	if ( res < 0) {
		printf("could not connect to server %d\n", res);
		//return 1;
	}

	// send

	// data that will be sent to the server
	const char* data_to_send = "Gangadhar Hi Shaktimaan hai";
	send(sock, data_to_send, strlen(data_to_send), 0);

	// receive

	int n = 0;
	int len = 0, maxlen = 100;
	char buffer[maxlen];
	char* pbuffer = buffer;

	// will remain open until the server terminates the connection
	while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
		pbuffer += n;
		maxlen -= n;
		len += n;

		buffer[len] = '\0';
		printf("received: '%s'\n", buffer);
	}

	// close the socket
	close(sock);
	return 0;
}


int windowWidth;
int windowHeight;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    printf("window_size_callback received width: %i, height: %i\n", width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int modifier)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE)
        glfwSetWindowShouldClose(window, 1);

    if (key == GLFW_KEY_ENTER)
        std::cout << "Enter was hit\n" << std::endl;
}

static void wmbutcb(GLFWwindow *window, int button, int action, int mods) {
    //assert(window != NULL); (void)button; (void)action; (void)mods;
    printf("Mouse buttion! \n");
}


GLFWwindow *window;

void do_frame(){
    static int a = 0;
    //printf("Fc: %d \n", ++a);
    //glClearColor(rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(int argc, char **argv) {


testSocket();

if (glfwInit()!=GL_TRUE) {
    printf("glfwInit() failed\n");
    glfwTerminate();
} else {
    printf("glfwInit() success\n");
    window = glfwCreateWindow(1280, 512, "GLFW test", NULL, NULL);
    if (!window){
        printf("glfwCreateWindow() failed\n");
        glfwTerminate();
    } else {
      printf("glfwCreateWindow() success\n");
      glfwMakeContextCurrent(window);
      glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
      glfwSetWindowSizeCallback(window, window_size_callback);
      glfwSetMouseButtonCallback(window, wmbutcb);
      glfwSetKeyCallback(window, key_callback);
      glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
#ifdef EMSCRIPTEN
      emscripten_set_main_loop(do_frame, 0, 1);
#else
      while (!glfwWindowShouldClose(window))
      {
          do_frame();
      }
#endif
    }
}

    glfwTerminate();
return EXIT_SUCCESS;
}