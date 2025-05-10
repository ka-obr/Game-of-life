import lib.Size;

public class game_of_life {
    public static void main(String[] args) {
        World world = new World(new Size(10, 10)); // Przykładowy rozmiar świata
        Gameplay gameplay = new Gameplay(world);
    }
}
