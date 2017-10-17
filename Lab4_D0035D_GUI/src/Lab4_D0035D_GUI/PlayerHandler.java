package Lab4_D0035D_GUI;

import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;


@SuppressWarnings("serial")
public class PlayerHandler extends Thread {

	private Socket socket;
	private DataOutputStream output;
	private DataInputStream input;
	private String msg;
	
	GameView theView;
	JavaServer server;
	
	public PlayerHandler(Socket socket, JavaServer server) {
		this.socket = socket;
		this.server = server;
		theView = new GameView();
		server = new JavaServer();
		//run();
	}
	
	public void run() {
		connect();
		whileConnected();
	}
	
	private void connect() {
		try {
			output = new DataOutputStream(socket.getOutputStream());
			input = new DataInputStream(socket.getInputStream());
			output.flush();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	private void whileConnected() {
		do{
			try {
				while(true) {
					System.out.println("Waiting for message...");
					byte[] recvBuf = new byte[2048];
					input.read(recvBuf);
					String msg = new String(recvBuf, StandardCharsets.UTF_8);
					System.out.println("This messag is from c++: " +msg+ "\n");
				}
			} catch (EOFException e){
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} while (!msg.equals("CLIENT - END\n"));
	}
}
	