
/**
 * This class is the user interface / GUI of the game
 * 
 * @author CHUNG Ka Lok, 3035781249
 *
 */


import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
 

public class User_interface {
	/**
	 *  @param t_panel The panel of welcome message
	 *  @param namefeild The panel to get user name
	 *  @param textfield The field for welcome message
	 *  @param bt_panel Stroing button 0 - 2
	 *  @param bt_panel2 Stroing button 3 - 5
	 *  @param bt_panel3 Stroing button 6 - 8
	 *  @param input Input panel for user name
	 *  @param bton The array of button 0 - 8
	 *  @param sumbit Check if user has enter and submit the name
	 *  @param frame The frame for the entire window
	 *  @param name_input The bar for entering user name
	 *  @param start Check is the game is started
	 *  @param move Check if it is player's turn
	 *  
	 */
	
	JPanel t_panel = new JPanel();
    JPanel namefeild = new JPanel();
    JLabel textfield = new JLabel();
    JPanel bt_panel = new JPanel();
    JPanel bt_panel2 = new JPanel();
    JPanel bt_panel3 = new JPanel();
    JPanel input = new JPanel();
    JButton[] bton = new JButton[9];
    JButton submit = new JButton();
    JFrame frame = new JFrame();
    JTextField name_input = new JTextField(20);
    boolean start = false;
    boolean move = true;
    
    public void construct() {
    	/**
    	 * This is to setup button 0 - 8
    	 */
    	for (int i = 0; i < 9; i++) {
            bton[i] = new JButton();
            bt_panel.add(bton[i]);
            bton[i].setFont(new Font("Ink Free", Font.BOLD, 50));
            bton[i].setFocusable(false);
        }
    }
    
    
	public void set() {
		/**
		 * this method is to set up the whole window
		 */
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 600);
        frame.setTitle("Tic Tac Toe");
        frame.setLayout(new BorderLayout(3,1));
        

        textfield.setFont(new Font("Times New Roman", Font.BOLD, 20));
        textfield.setText("Enter your player name...");
        textfield.setOpaque(true);

        t_panel.setLayout(new BorderLayout());
        t_panel.setBounds(0, 0, 800, 100);

        bt_panel.setSize(200,200);
        bt_panel.setLayout(new GridLayout(3, 3));
               
        
        namefeild.add(name_input);
               
        
        submit.setFont(new Font("Arial", Font.BOLD, 10));
        submit.setText("Submit");
        
        namefeild.add(submit);
        input.add(namefeild);
        
        
        t_panel.add(textfield);
        
        JMenuBar menuBar = new JMenuBar();
		JMenu menu = new JMenu ("Control");
		JMenuItem exit = new JMenuItem("Exit");
		JMenu help = new JMenu ("Help");
		JMenuItem rule = new JMenuItem("Instruction");
		menu.add(exit);
		help.add(rule);
		menuBar.add(menu);
		menuBar.add(help);
		frame.setJMenuBar(menuBar);
		
        frame.add(t_panel, BorderLayout.NORTH);
        frame.add(bt_panel,BorderLayout.CENTER);
        frame.add(namefeild,BorderLayout.SOUTH);
        
        frame.setVisible(true);
        
        submit.addActionListener(new ActionListener() {
    		public void actionPerformed(ActionEvent e) {
    			/**
    			 * this is the action listener of the submit button, which is for submitting the user name
    			 */
    			String input = name_input.getText();
    			textfield.setText("Welcome " + input + " !");
    			name_input.setEnabled(false);
    			submit.setEnabled(false);
    			start = true;
    			frame.setTitle("Tic Tac Toe-Player: " + input);
    		}
    	});
        
        exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				/**
				 * The action listener for the "exit" button in menubar
				 */
				//frame.setVisible(false); 
				//frame.dispose(); 
				System.exit(0);
			}
		});
        
        rule.addActionListener(new ActionListener() {
        	
        	public void actionPerformed(ActionEvent e) {
        		/**
        		 * The action listener for the "help" bar
        		 */
        		JFrame message = new JFrame();  
				JOptionPane.showMessageDialog(message,
						"Some information about the game:" + '\n' +
						"Criteria for a valid move:" + '\n' +
						"- The move is not occupied by any mark." + '\n' +
						"- The move is made in the player¡¦s turn." + '\n' +
						"- The move is made within the 3 x 3 board." + '\n' +
						"The game would continue and switch among the opposite player until it reaches either one of the following conditions:" +
						'\n' + "- Player 1 wins." + '\n'+
						"- Player 2 wins." + '\n' + "- Draw.");
			}
        });

    
	}
	
	public JButton one() {
		/**
		 * return button 0
		 */
		return bton[0];
	}
	
	public JButton two() {
		/**
		 * return button 1
		 */
		return bton[1];
	}
	
	public JButton three() {
		/**
		 * return button 2
		 */
		return bton[2];
	}
	
	public JButton four() {
		/**
		 * return button 3
		 */
		return bton[3];
	}
	
	public JButton five() {
		/**
		 * return button 4
		 */
		return bton[4];
	}
	
	public JButton six() {
		/**
		 * return button 5
		 */
		return bton[5];
	}
	
	public JButton seven() {
		/**
		 * return button 6
		 */
		return bton[6];
	}
	
	public JButton eight() {
		/**
		 * return button 7
		 */
		return bton[7];
	}
	
	public JButton nine() {
		/**
		 * return button 8
		 */
		return bton[8];
	}

	public void update(String command) {
		/**
		 * return button update the button content when new input is made
		 */
		
		// TODO Auto-generated method stub
		for (int i = 0; i < 9; i++) {
			String text = command.substring(i, i + 1);
			if (text.equals("X")) {
				bton[i].setText(text);
				bton[i].setForeground(new Color(0, 0, 0));
			} else if (text.equals("O")) {
				bton[i].setText(text);
				bton[i].setForeground(new Color(255, 0, 0));
			}
		}
	}

	public void lose() {
		/**
		 *  Show losing message
		 */
	
	
		// TODO Auto-generated method stub
		JFrame message = new JFrame();  
		JOptionPane.showMessageDialog(message, "You lose");
		
	}


	public void quit() {
		/**
		 * 
		 * show message saying that one player has quitted
		 */
		// TODO Auto-generated method stub
		JFrame message = new JFrame();  
		JOptionPane.showMessageDialog(message,
				"Geme End. One of the player left");
	}


	public void waiting() {
		/**
		 * show wait message when it is not player's turn
		 */
		// TODO Auto-generated method stub
		textfield.setText("Wait for your oppoent");
	}


	public void move() {
		// TODO Auto-generated method stub
		/**
		 * show wait message when it is the player's turn
		 */
		textfield.setText("Your oppoent has moved, now it is your turn");
	}


	public void win() {
		// TODO Auto-generated method stub
		/**
		 * show winning message
		 */
		JFrame message = new JFrame();  
		JOptionPane.showMessageDialog(message,
				"You Win!");
	}


	public void draw() {
		// TODO Auto-generated method stub
		/**
		 * show the message when draw
		 */
		JFrame message = new JFrame();  
		JOptionPane.showMessageDialog(message,
				"Draw");
	}


	public void start() {
		// TODO Auto-generated method stub
		/**
		 * show the message to start the game
		 */
		textfield.setText("You are Player One. Please make your move");
	}


	
	
	
}
