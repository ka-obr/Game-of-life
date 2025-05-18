import javax.swing.*;
import java.awt.*;
  
public class Sheep extends Animal {
    private static final ImageIcon sheepIcon = new ImageIcon("images/sheep.png");
    public static final Image scaledSheepIcon = sheepIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Sheep(Point position, World world, int age) {
        super(4, 4, position, world, age);
    }
  
    @Override
    public ImageIcon getIcon() {
        return sheepIcon;
    }
}
