
/**
 * This is the Player class for the card game
 * 
 * @author Chung Ka Lok, 3035781249
 * 
 */

public class Player {
	
	/**
	 * @param amount The amount of money the player has
	 * @param card1 The value of the 1st card of the player
	 * @param card2 The value of the 2nd card of the player
	 * @param card3 The value of the 3rd card of the player
	 */
	
	int amount = 100;
	int card1 = 0;
	int card2 = 0;
	int card3 = 0;
	
	/**
	 * This method construct the player class, and set the variable to default value
	 */
	public Player() {
		this.amount = 100;
		this.card1 = 0;
		this.card2 = 0;
		this.card3 = 0 ;
	}
	
	/**
	 * This method deduct the amount of bet from player's money when the player loses
	 * @param bet The amount of bet the player made in that round
	 */
	public void failed(int bet) {
		amount = amount - bet;
	}
	
	/** 
	 * This method add the amount of bet from player's money when the player loses
	 * @param bet The amount of bet the player made in that round
	 */
	public void win(int bet) {
		amount = amount + bet;
	}
	
	/**
	 * This function reset the player information, 
	 * to default value when the player start a new game
	 */
	public void reset() {
		this.amount = 100;
		this.card1 = 0;
		this.card2 = 0;
		this.card3 = 0 ;
	}
	
	/**
	 * This method return the remainder of the cards value
	 * @return ans The value of the remainder of the cards
	 */
	public int remainder() {
		int ans = 0;
		if (isNormal(this.card1)) {
			ans = ans + card1 % 100;
		}
		if (isNormal(this.card2)) {
			ans = ans + card2 % 100;
		}
		if (isNormal(this.card3)) {
			ans = ans + card3 % 100;
		}
		return ans % 10;
	}
	
	/**
	 * The method return the number of special card the player has
	 * @return ans The number of player's special cards
	 */
	public int unique() {
		int ans = 0;
		if (!isNormal(this.card1)) {
			ans++;
		}
		if (!isNormal(this.card2)) {
			ans++;
		}
		if (!isNormal(this.card3)) {
			ans++;
		}
		return ans;
	}
	
	/**
	 * The method return whether the card is a special card or not,
	 * TRUE if it is not special, FALSE if the card is J,Q,K
	 * @param num The number of the card
	 */
	public boolean isNormal(int num) {
		return (num % 100 <= 10);
	}

}
