
/**
 * This class is the client side of the game
 * 
 * @author CHUNG Ka Lok, 3035781249
 *
 */

import java.io.*;  
import java.net.*;
import java.awt.event.*;
import java.io.PrintWriter;

public class Client {
	/**
	 *  @param sock The client socket
	 *  @param writer Client's Printwriter
	 *  @param side The side (X or O) of the player
	 *  @param assignws To tell if player has been assigned the side (X or O)
	 *  @param view The GUI for the client
	 */
	Socket sock;
	PrintWriter writer;
	String side = " ";
	boolean assigned = false;
	boolean print = false;
	User_interface view = new User_interface();
	
	public void go() { 
		/**
		 * This function start the client side and connect to the server
		 */
		
		view.construct();
		view.one().addActionListener(new one());
		view.two().addActionListener(new two());
		view.three().addActionListener(new three());
		view.four().addActionListener(new four());
		view.five().addActionListener(new five());
		view.six().addActionListener(new six());
		view.seven().addActionListener(new seven());
		view.eight().addActionListener(new eight());
		view.nine().addActionListener(new nine());
		view.set();
		boolean go = false;
		while (go == false) {
			go = view.start;
			System.out.print("");
		}
		
		
		try {
			System.out.println("connecting...");
			sock = new Socket("127.0.0.1", 5000); 
			
			
			
			writer = new PrintWriter(sock.getOutputStream());  

			InputStreamReader streamReader = new InputStreamReader(sock.getInputStream());  
			BufferedReader reader = new BufferedReader(streamReader);  
			
			//side =  reader.readLine();
			//System.out.println("I am " + side);
			//writer.println("READY");
			
			String command ;
			while ((command = reader.readLine()) != null) {
				
				if (command.substring(0, 1).equals("U")) { //update
					System.out.println(side + command);
					view.update(command.substring(1, 10));
				}
				if (command.substring(0, 1).equals("L")) {// end
					System.out.println(side + command);
					view.update(command.substring(1, 10));
					if(command.substring(10, 11).equals(side)) {
						view.win();
					} else if (command.substring(10, 11).equals("D")) {
						view.draw();
					} else {
						view.lose();
					}
				}
				if (command.substring(0, 1).equals("Q")) {// quit
					System.out.println(side + command);
					view.quit();
				}
				if (command.substring(0, 1).equals("W")) {// wait
					System.out.println(side + command);
					view.move = false;
					view.waiting();
				}
				if (command.substring(0, 1).equals("E")) {// my turn
					System.out.println(side + command);
					if(command.substring(1, 2).equals("1")) {
						view.start();
					} else {
						view.move = true;
						view.move();
					}
					
					//writer.println("testing");
					
				}
				if (command.substring(0, 1).equals("X") && side != "X" && side != "O") {
					
					System.out.println("I am " + command);
					assigned = true;
					side = "X";
				}
				if ( command.substring(0, 1).equals("O")  && side != "X" && side != "O") {
					
					System.out.println("I am " + command);
					assigned = true;
					side = "O";
				}
				System.out.println(command + " whole loop");
				
				
			}

		} catch (Exception ex) { 
			ex.printStackTrace(); 
		}
	}
	
	
	class one implements ActionListener{
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 0 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[0].getText() != "X" && view.bton[0].getText() != "O" && view.move == true) {
				writer.println("0");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 0");
			
		}
		
	}
	
	class two implements ActionListener{
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 1 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[1].getText() != "X" && view.bton[1].getText() != "O" && view.move == true) {
				writer.println("1");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 1");
			
		}
		
	}
	class three implements ActionListener{

		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 2 of the table
		 *
		 */
		
		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[2].getText() != "X" && view.bton[2].getText() != "O" && view.move == true) {
				writer.println("2" );
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 2");
		}
		
	}
	class four implements ActionListener{
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 3 of the table
		 *
		 */
		

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[3].getText() != "X" && view.bton[3].getText() != "O" && view.move == true) {
				writer.println("3" );
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 3");
		}
		
	}
	class five implements ActionListener{
		
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 4 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[4].getText() != "X" && view.bton[4].getText() != "O" && view.move == true) {
				writer.println("4");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 4");
		}
		
	}
	class six implements ActionListener{
		
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 5 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[5].getText() != "X" && view.bton[5].getText() != "O" && view.move == true) {
				writer.println("5");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 5");
		}
		
	}
	class seven implements ActionListener{
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 7 of the table
		 *
		 */
		

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[6].getText() != "X" && view.bton[6].getText() != "O" && view.move == true) {
				writer.println("6");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 6");
		}
		
	}
	class eight implements ActionListener{
		
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 8 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[7].getText() != "X" && view.bton[7].getText() != "O" && view.move == true) {
				writer.println("7");
				writer.flush();
				System.out.print("Valid ");
			}
			System.out.println("click 7");
		}
		
	}
	class nine implements ActionListener{
		
		/**
		 * 
		 * The table is 3X3, each button is:
		 * 0 1 2
		 * 3 4 5
		 * 6 7 8
		 * 
		 * This is the action listener of button 8 of the table
		 *
		 */

		//@Override
		public void actionPerformed(ActionEvent e) {
			// TODO Auto-generated method stub
			if (view.bton[8].getText() != "X" || view.bton[8].getText() != "O" && view.move == true) {
				writer.println("8");
				writer.flush();
				System.out.print("Valid ");
			} 
			System.out.println("click 8");
		}
		
	}
	
	/**
	 * 
	 * This is the main() for client and start the program
	 */
	
	public static void main(String[] args) {
		Client d = new Client();
		d.go();
	}
}