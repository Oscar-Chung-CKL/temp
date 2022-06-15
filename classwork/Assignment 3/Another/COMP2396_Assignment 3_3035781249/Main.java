import java.awt.*;
import java.awt.event.* ;
import java.util.ArrayList;
import java.util.Collections;
import javax.swing.* ;
/**
 * 
 * This is the main java class for the card game
 * @author Chung Ka Lok, 3035781249
 * 
 */
public class Main   {
	/**
	 * This is the main class variables
	 * 
	 * @param label_Image1 1st card for dealer
 	 * @param label_Image2 2nd card for dealer
 	 * @param label_Image3 3rd card for dealer
 	 * @param label_Image4 1st card for player
 	 * @param label_Image5 2nd card for player
 	 * @param label_Image6 3rd card for player
	 */
	JLabel label_Image1 = new JLabel();
	JLabel label_Image2 = new JLabel();
	JLabel label_Image3 = new JLabel();
	JLabel label_Image4 = new JLabel();
	JLabel label_Image5 = new JLabel();
	JLabel label_Image6 = new JLabel();
	
	/**
	 * 
	 * @param btn_rpcard1 Replace button for 1st card of player
	 * @param btn_rpcard2 Replace button for 2nd card of player
	 * @param btn_rpcard3 Replace button for 3rd card of player
	 * @param btn_rpcard_start Button to start the game/round
	 * @param btn_rpcard_end Button to end the round/game
	 * 
	 */
	JButton btn_rpcard1 = new JButton("Replace Card 1");
	JButton btn_rpcard2 = new JButton("Replace Card 2");
	JButton btn_rpcard3 = new JButton("Replace Card 3");
	JButton btn_rpcard_start = new JButton("Start");
	JButton btn_rpcard_result = new JButton("Result");
	
	/**
	 * @param label_bet Label to get user input foe the amount of bet
	 * @param lable_info Label to display how much has the player bet
	 * @param lable_money Lable to show how much money player has
	 * @param txt_inputbet Input bar to get player input for the amount of bet
	 */
	JLabel label_bet = new JLabel("Bet : $");
	JLabel label_info = new JLabel("Please place your bet !");
	JLabel label_money = new JLabel("Amount of money you have: $100");
	
	JTextField txt_inputbet = new JTextField(10);
	
	/**
	 * @param Image1 Image of the 1st card for dealer
 	 * @param Image2 Image of the 2nd card for dealer
 	 * @param Image3 Image of the 3rd card for dealer
 	 * @param Image4 Photo of the 1st card for player
 	 * @param Image5 Photo of the 2nd card for player
 	 * @param Image6 Photo of the 3rd card for player
	 */
	ImageIcon Image1 = new ImageIcon("Images/Images/0.gif");
	ImageIcon Image2 = new ImageIcon("Images/Images/0.gif");
	ImageIcon Image3 = new ImageIcon("Images/Images/0.gif");
	ImageIcon Image4 = new ImageIcon("Images/Images/0.gif");
	ImageIcon Image5 = new ImageIcon("Images/Images/0.gif");
	ImageIcon Image6 = new ImageIcon("Images/Images/0.gif");
	
	/**
	 * @param player Player class object for the game
	 * @param dealer Dealer class object for the game
	 */
	Player player = new Player();
	Dealer dealer = new Dealer();
	
	/**
	 * @param MainPanel The main panel for the game
	 * @param DealerPanel The dealer panel to show dealer's cards
	 * @param PlayerPanle The panel to show player's cards
	 * @param RpCardBtnPanel The panel to show "Replace card" buttons
	 * @param ButtonPanel The Panel to show "start" and "result" buttons
	 * @param InfoPanel The panel to shows all the labels containing game information
	 */

	JPanel MainPanel = new JPanel();
	JPanel DealerPanel = new JPanel();
	JPanel PlayerPanel = new JPanel();
	JPanel RpCardBtnPanel = new JPanel();
	JPanel ButtonPanel = new JPanel();
	JPanel InfoPanel = new JPanel();
		
	/**
	 * @param started Whether the round/game has started
	 * @param replace The number of time the player replaces a card
	 * @param replace1 Whether player's card1 has been replaced
	 * @param replace2 Whether player's card2 has been replaced
	 * @param replace3 Whether player's card3 has been replaced
	 * @param bet The amount of player bet
	 */
	boolean started = false;
	int replace = 0;
	boolean replace1 = false;
	boolean replace2 = false;
	boolean replace3 = false;
	int bet = 0;
	
	/**
	 * @param shuffled The ArrayList storing the 52 shuffled cards
	 * @param game the game class object in Main
	 */
	ArrayList<Integer> shuffled = new ArrayList<Integer>();
	
	static Main game = new Main();
	
	/**
	 * This main() initialize the game setting and set up the game
	 * 
	 */
	public static void main(String[] args) {
		
		game.shuffling();
		game.initial();
		game.setup();
		
	}
	
	/**
	 * This method initialize the cards of dealer and player
	 */
	public void initial() {
		
		dealer.card1 = shuffled.get(0);
		shuffled.remove(0);
		dealer.card2 = shuffled.get(0);
		shuffled.remove(0);
		dealer.card3 = shuffled.get(0);
		shuffled.remove(0);
		
		player.card1 = shuffled.get(0);
		shuffled.remove(0);
		player.card2 = shuffled.get(0);
		shuffled.remove(0);
		player.card3 = shuffled.get(0);
		shuffled.remove(0);
		
	}
	
	
	/**
	 * This method shuffle all 52 cards into the ArrayList randomly
	 */
	public void shuffling() {
		for (int i = 101; i < 114; i++) {
			shuffled.add(i);
		}
		for (int i = 201; i < 214; i++) {
			shuffled.add(i);
		}
		for (int i = 301; i < 314; i++) {
			shuffled.add(i);
		}
		for (int i = 401; i < 414; i++) {
			shuffled.add(i);
		}
		Collections.shuffle(shuffled);
	}
	
	/**
	 * This method let the game continue if the player still have money to bet, 
	 * first initialize everything again and let the player to continue playing
	 */
	public void ongoing() {
		
		game.clearShuddled();
		game.shuffling();
		game.initial();
		
		bet = 0;
		started = false;
		replace = 0;
		replace1 = false;
		replace2 = false;
		replace3 = false;
		label_money.setText("Amount of money you have: $" + player.amount);
		label_info.setText("Please place your bet !");
		
		Image1 = new ImageIcon("Images/Images/0.gif");
		Image2 = new ImageIcon("Images/Images/0.gif");
		Image3 = new ImageIcon("Images/Images/0.gif");
		Image4 = new ImageIcon("Images/Images/0.gif");
		Image5 = new ImageIcon("Images/Images/0.gif");
		Image6 = new ImageIcon("Images/Images/0.gif");
		
		label_Image1.setIcon(Image1);
		label_Image2.setIcon(Image2);
		label_Image3.setIcon(Image3);
		label_Image4.setIcon(Image4);
		label_Image5.setIcon(Image5);
		label_Image6.setIcon(Image6);
	}
	
	/**
	 * This setup() function initialize the display panel and let the player to play
	 */
	public void setup() {
		
		label_Image1.setIcon(Image1);
		label_Image2.setIcon(Image2);
		label_Image3.setIcon(Image3);
		label_Image4.setIcon(Image4);
		label_Image5.setIcon(Image5);
		label_Image6.setIcon(Image6);
						
		DealerPanel.add(label_Image1);
		DealerPanel.add(label_Image2);
		DealerPanel.add(label_Image3);
		
		PlayerPanel.add(label_Image4);
		PlayerPanel.add(label_Image5);
		PlayerPanel.add(label_Image6);
		
		RpCardBtnPanel.add(btn_rpcard1);
		RpCardBtnPanel.add(btn_rpcard2);
		RpCardBtnPanel.add(btn_rpcard3);
				
		ButtonPanel.add(label_bet);
		ButtonPanel.add(txt_inputbet);
		ButtonPanel.add(btn_rpcard_start);
		ButtonPanel.add(btn_rpcard_result);
		
		InfoPanel.add(label_info);
		InfoPanel.add(label_money);
				
		MainPanel.setLayout(new GridLayout(5,1));
		MainPanel.add(DealerPanel);
		MainPanel.add(PlayerPanel);
		MainPanel.add(RpCardBtnPanel);
		MainPanel.add(ButtonPanel);
		MainPanel.add(InfoPanel);
				
		DealerPanel.setBackground(Color.green);
		PlayerPanel.setBackground(Color.green);
		RpCardBtnPanel.setBackground(Color.green);
				
		JFrame frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		JMenuBar menuBar = new JMenuBar();
		JMenu menu = new JMenu ("Control");
		JMenuItem exit = new JMenuItem("Exit");
		menu.add(exit);
		menuBar.add(menu);
		frame.setJMenuBar(menuBar);
		frame.getContentPane().add(MainPanel);
		frame.setTitle("A Simple Card Game");
		frame.setSize(400, 700);
		frame.setVisible(true);
		
		/**
		 * This method override the ActionListner of the "start" button,
		 * if player bet is higher than the amount of money the player has,
		 * a warning will be shown in pop-up message way.
		 * Else, the player card is displayed.
		 */
		btn_rpcard_start.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				String input;
				input = txt_inputbet.getText();
				bet = Integer.valueOf(input);
				if (bet > player.amount) {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU DO NOT HAVE ENOUGH MONEY TO BET");
					    
				} else {
					started = true;
					
					label_info.setText("Your current bet is:$" + bet);
					label_money.setText("Amount of money you have: $" 
							+ player.amount);
					
					String name1 = "Images/Images/" + 
							String.valueOf(player.card1) + ".gif";
					String name2 = "Images/Images/" + 
							String.valueOf(player.card2) + ".gif";
					String name3 = "Images/Images/" + 
							String.valueOf(player.card3) + ".gif";
					
					Image4 = new ImageIcon(name1);
					Image5 = new ImageIcon(name2);
					Image6 = new ImageIcon(name3);
					label_Image4.setIcon(Image4);
					label_Image5.setIcon(Image5);
					label_Image6.setIcon(Image6);
				}
			}
		} );
		
		/**
		 * The method is for the ActionListener of "Result" button.
		 * if the game has not started, a pop-up message is shown,
		 * and it will ask player to start the game/round first.
		 * If the game is started, display dealer's cards,
		 * then check whoever wins the game,
		 * and show the message in a pop-up window.
		 * 
		 * If player still has money, continue the game,
		 * else, shows a pop-up message of "Game over", 
		 * and ask the player to start a new game
		 */
		btn_rpcard_result.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				if (started == true) {
					
					String name1 = "Images/Images/" + 
							String.valueOf(dealer.card1) + ".gif";
					String name2 = "Images/Images/" + 
							String.valueOf(dealer.card2) + ".gif";
					String name3 = "Images/Images/" + 
							String.valueOf(dealer.card3) + ".gif";
					Image1 = new ImageIcon(name1);
					Image2 = new ImageIcon(name2);
					Image3 = new ImageIcon(name3);
					label_Image1.setIcon(Image1);
					label_Image2.setIcon(Image2);
					label_Image3.setIcon(Image3);
					
					
					if (player.unique() > dealer.unique() && player.unique() != dealer.unique()) {
						//player win
						
						player.win(bet);
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								"Congrauations! You win this round!");
					} else if (player.unique() < dealer.unique() && player.unique() != dealer.unique()) {
						//dealer win
						player.failed(bet);
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								"Sorry! The Dealer wins this round!");
					} else if (player.remainder() > dealer.remainder() && player.remainder() != dealer.remainder()) {
						//player win
						player.amount = player.amount + bet;
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								"Congrauations! You win this round!");
					} else if (player.remainder() < dealer.remainder() && player.remainder() != dealer.remainder()) {
						//dealer win
						player.failed(bet);
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								"Sorry! The Dealer wins this round!");
					} else {
						//dealer win
						player.failed(bet);
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								"Sorry! The Dealer wins this round!");
					}
					
					if (player.amount > 0) {
						game.ongoing();
					} else {
						String text;
						text = "Game over!" + '\n' + "You have no more money!"
								+ '\n' + "Please start a new game!";
						JFrame message = new JFrame();  
						JOptionPane.showMessageDialog(message,
								text);
						game.reset();
						game.ongoing();
					}
					
				} else {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"Please start the game first");
				}
			}
		});
		
		/**
		 * This overrides the action of "Replace Card 1" button.
		 * If the game has not started, ask the player to start first via pop-up window.
		 * Else if the game already started,
		 * if the number of replace is less than 2 AND the card has not been replaced yet,
		 * allow the replacement and display a new card,
		 * else use a pop-up message to warn the player
		 */
		btn_rpcard1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				if (started == false) {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"Please start the game first");
					return;
				}
				
				if (started == true && replace < 2 && replace1 == false) {
					replace++;
					replace1 = true;
					
					player.card1 = shuffled.get(0);
					shuffled.remove(0);
					
					String name1 = "Images/Images/" + 
							String.valueOf(player.card1) + ".gif";
					Image4 = new ImageIcon(name1);
					label_Image4.setIcon(Image4);
					
					
				} else if (replace1 == true && replace < 2){
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN ONLY REPLACE THE SAME CARD ONCE");
				} else if (replace1 == false && replace >= 2){
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				} else {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				}
			}
		});
		
		/**
		 * This overrides the action of "Replace Card 2" button.
		 * If the game has not started, ask the player to start first via pop-up window.
		 * Else if the game already started,
		 * if the number of replace is less than 2 AND the card has not been replaced yet,
		 * allow the replacement and display a new card,
		 * else use a pop-up message to warn the player
		 */
		btn_rpcard2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				if (started == false) {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"Please start the game first");
					return;
				}
				
				if (started == true && replace < 2 && replace2 == false) {
					replace++;
					replace2 = true;
					
					player.card2 = shuffled.get(0);
					shuffled.remove(0);
					
					String name2 = "Images/Images/" + 
							String.valueOf(player.card2) + ".gif";
					Image5 = new ImageIcon(name2);
					label_Image5.setIcon(Image5);
					
				} else if (replace2 == true && replace < 2 ){
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN ONLY REPLACE THE SAME CARD ONCE");
				} else if (replace2 == false && replace >= 2){
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				} else {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				}
			}
		});
		
		/**
		 * This overrides the action of "Replace Card 3" button.
		 * If the game has not started, ask the player to start first via pop-up window.
		 * Else if the game already started,
		 * if the number of replace is less than 2 AND the card has not been replaced yet,
		 * allow the replacement and display a new card,
		 * else use a pop-up message to warn the player
		 */
		btn_rpcard3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				
				if (started == false) {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"Please start the game first");
					return;
				}
				
				if (started == true && replace < 2 && replace3 == false) {
					replace++;
					replace3 = true;

					player.card3 = shuffled.get(0);
					shuffled.remove(0);
					
					String name3 = "Images/Images/" + 
							String.valueOf(player.card3) + ".gif";
					Image6 = new ImageIcon(name3);
					label_Image6.setIcon(Image6);
					
				} else if (replace3 == true && replace < 2) {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN ONLY REPLACE THE SAME CARD ONCE");
				} else if (replace3 == false && replace >= 2){
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				} else {
					JFrame warning = new JFrame();  
					JOptionPane.showMessageDialog(warning,
						"YOU CAN REPLACE AT MOST TWO CARDS");
				}
			}
		});
		
		/**
		 * This method is for the menu bar items,
		 * when the "Exit" in the menu bar is clicked, close the game and the window
		 */
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				frame.setVisible(false); 
				frame.dispose(); 
			}
		});
	}

	/**
	 * This method is to reset all the game setting when the player has no money left
	 */
	public void reset() {
		player.reset();
		dealer.reset();
		game.clearShuddled();
		game.shuffling();
		bet = 0;
		bet = 0;
		started = false;
		replace = 0;
		replace1 = false;
		replace2 = false;
		replace3 = false;
		label_money.setText("Amount of money you have: $" + player.amount);
		label_info.setText("Please place your bet !");
		
		Image1 = new ImageIcon("Images/Images/0.gif");
		Image2 = new ImageIcon("Images/Images/0.gif");
		Image3 = new ImageIcon("Images/Images/0.gif");
		Image4 = new ImageIcon("Images/Images/0.gif");
		Image5 = new ImageIcon("Images/Images/0.gif");
		Image6 = new ImageIcon("Images/Images/0.gif");
		
		label_Image1.setIcon(Image1);
		label_Image2.setIcon(Image2);
		label_Image3.setIcon(Image3);
		label_Image4.setIcon(Image4);
		label_Image5.setIcon(Image5);
		label_Image6.setIcon(Image6);
	}
	
	/**
	 * This method is used to clear the ArrayList shuffled after each round
	 */
	public void clearShuddled() {
		shuffled.removeAll(shuffled);
	}
	
}
