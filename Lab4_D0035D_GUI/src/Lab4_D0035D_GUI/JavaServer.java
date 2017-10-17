package Lab4_D0035D_GUI;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class JavaServer {

	private ServerSocket serverSocket;
	private Socket socket;
	private String ip;
	private int port = 9876;
	
	public JavaServer(){
		setupSocket();
	}
	
	private void setupSocket() {
		try{
			serverSocket = new ServerSocket(port);
			System.out.println("Java Socket created..");
			while(true) {
				whileConnected();
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	
	private void whileConnected() {
		try {
			System.out.println("Waiting for connect...");
			socket = serverSocket.accept();
			System.out.println("Connect Success..");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
