
/**
 * This class is the server side of the game
 * 
 * @author CHUNG_Ka_Lok, 3035781249
 *
 */

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Server {
	/**
	 *  @param serverSock The server socket
	 *  @param writers The arraylist storing all client Printwriter
	 *  @param number Number of player connecting the server
	 *  @param assign To tell if player has been assigned the side (X or O)
	 *  @param content The content of the game table
	 *  @param sock The socket for client 1
	 *  @param sock2 The socket for client 2
	 *  @param writer1 The Printwriter of client 1
	 *  @param writer2 Printwaiter for client 2
	 *  @param reader The BufferedReader for client 1
	 *  @param reader2 The BufferedReader for client 2
	 *  @param streamReader The InputStreamReader for client 1
	 *  @param streamReader2 The InputStreamReader for client 2
	 *  
	 */
	ServerSocket serverSock;
	ArrayList<PrintWriter> writers = new ArrayList<PrintWriter>();
	int number = 0;
	boolean assign = false;
	String content = "012345678";
	Socket sock;
	Socket sock1;
	PrintWriter writer;  
	PrintWriter writer2;
	BufferedReader reader;
	BufferedReader reader2;
	InputStreamReader streamReader;
	InputStreamReader streamReader2;
	
	/**
	 * 
	 * This is the main class of the server and the game
	 * 
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {  
		Server server = new Server(); 
		//System.out.println(content);
		server.go();
		server.play();
	}

	/**
	 * This is for receiving client connection
	 */

	public void go() {  
		try {
			serverSock = new ServerSocket(5000);
			System.out.println("Server 2 is running...");
			
			while (true) {
				if (number == 0) {
					sock = serverSock.accept();
					System.out.println("Server is connected to client 1");
					
					
					streamReader = new InputStreamReader(sock.getInputStream());  
					reader = new BufferedReader(streamReader); 
					
					writer = new PrintWriter(sock.getOutputStream(), true);  
					writers.add(writer);
					//clientThread.start();
					number++;
				}
				if (number == 1) {
					sock1 = serverSock.accept();
					System.out.println("Server is connected to client 2");
					
					
					streamReader2 = new InputStreamReader(sock1.getInputStream());  
					reader2 = new BufferedReader(streamReader2); 
					//clientThread2.start();
					//clientThread.start();
					//clientThread2.start();
					
					writer2 = new PrintWriter(sock1.getOutputStream(), true);  
					writers.add(writer2);
					
					number++;
				}
				if (number >= 2) {
					number++;
					break;
				}
				
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	} // close go
	
	private void play() throws IOException {
		// TODO Auto-generated method stub
		String command = "" ;
		//String newContent = "" ;
		int idx = -1;
		
		writer.println("X");
		writer.flush();
		writer2.println("O");
		writer2.flush();
		
		boolean start = false;
		
		try {
			
			
			while (true) {
				
				if (sock.isClosed()) {
					System.out.println("1 down");
				}
				if (sock1.isClosed()) {
					System.out.println("2 down");
				} //-----------------------------
				
				if (start == false) {
					writer.println("S");
					writer.flush();
					start = true;
				}
				if (matchEmpty() == true) {
					writer.println("E1");
					writer.flush();
				} else {
					writer.println("E2");
					writer.flush();
				}
				
				writer2.println("W + 1");
				writer2.flush();
				command = reader.readLine();
				idx = Integer.valueOf(command.substring(0, 1));
				content = content.substring(0,idx)+ "X" + content.substring(idx + 1, 9);
				for (PrintWriter eachWriter: writers) {
					eachWriter.println("U" + content);
				}
				
				if (matchOver().equals("X") || matchOver().equals("O") ) {
					System.out.println(content + " over 1 ");
					writer.println("L" + content + matchOver());
					writer.flush();
					writer2.println("L" + content + matchOver());
					writer2.flush();
				} else if (matchDraw() == true) {
					System.out.println(content + " draw 1 ");
					writer.println("L" + content + "D hi 1");
					writer.flush();
					writer2.println("L" + content + "D");
					writer2.flush();
				}
				
				//============
				if (sock.isClosed()) {
					System.out.println("1 down");
				}
				if (sock1.isClosed()) {
					System.out.println("2 down");
				}
				//=================
				
				System.out.println(content + " X");
				
				writer.println("W + 2");
				writer.flush();
				writer2.println("E + 2");
				writer2.flush();
				command = reader2.readLine();
				idx = Integer.valueOf(command.substring(0, 1));
				content = content.substring(0,idx)+ "O" + content.substring(idx + 1, 9);
				for (PrintWriter eachWriter: writers) {
					eachWriter.println("U" + content);
				}
				if (matchOver().equals("X") || matchOver().equals("O") ) {
					System.out.println(content + " over ");
					writer.println("L" + content + matchOver());
					writer.flush();
					writer2.println("L" + content + matchOver());
					writer2.flush();
				} else	if (matchDraw() == true) {
					System.out.println(content + " draw ");
					writer.println("L" + content + "D hihi");
					writer.flush();
					writer2.println("L" + content + "D");
					writer2.flush();
				}
				//-----
				if (sock.isClosed()) {
					System.out.println("1 down");
				}
				if (sock1.isClosed()) {
					System.out.println("2 down");
				}
				//-----
				System.out.println(content + " O");
			}
		} catch (Exception ex){
			writer2.println("Q");
			writer2.flush();
			writer.println("Q");
			writer.flush();
		}
		
	}
	
	private boolean matchEmpty() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 9; i++) {
			if (content.substring(i,i+1).equals("X")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("O")) {
				
				return false;
			}
		}
		return true;
	}



	private boolean matchDraw() {
		// TODO Auto-generated method stub
		for (int i = 0; i < 9; i++) {
			if (content.substring(i,i+1).equals("0")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("1")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("2")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("3")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("4")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("5")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("6")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("7")) {
				
				return false;
			} else if (content.substring(i,i+1).equals("8")) {
				
				return false;
			}
		}
		return true;
	}

	/**
	 * This check if the match is over
	 * @return The winner (X / O)
	 */
	public String matchOver() {
		
		if (content.substring(0,1).equals(content.substring(3,4)) && content.substring(0,1).equals(content.substring(6,7))) {
			
			return content.substring(0,1); // 0 3 6
			
		} else if (content.substring(1,2).equals(content.substring(4,5)) && content.substring(7,8).equals(content.substring(1,2)))
		{
			return content.substring(1,2); // 1 4 7
			
		}else if (content.substring(2,3).equals(content.substring(5,6)) && content.substring(5,6).equals(content.substring(8,9))) {
			
			return content.substring(8,9); // 2 5 8
			
		}else if (content.substring(0,1).equals(content.substring(1,2)) && content.substring(0,1).equals(content.substring(2,3))) {
			
			return content.substring(0,1); // 0 1 2
			
		}else if (content.substring(3,4).equals(content.substring(4,5)) && content.substring(5,6).equals(content.substring(4,5))) {
			
			return content.substring(3,4); // 3 4 5 
			
		}else if (content.substring(6,7).equals(content.substring(7,8)) && content.substring(7,8).equals(content.substring(8,9))) {
			
			return content.substring(8,9); // 6 7 8
			
		}else if (content.substring(0,1).equals(content.substring(4,5)) && content.substring(4,5).equals(content.substring(8,9))) {
			
			return content.substring(0,1); // 0 4 8
			
		}else if (content.substring(2,3).equals(content.substring(4,5)) && content.substring(4,5).equals(content.substring(6,7))) {
			
			return content.substring(6,7); // 2 4 6
		}
		return " ";
	}
}
