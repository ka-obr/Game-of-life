import javax.swing.*;
import java.awt.*;

public class Dandelion extends Plant {
    private static final ImageIcon dandelionIcon = new ImageIcon("images/dandelion.png");
    public static final Image scaledDandelionIcon = dandelionIcon.getImage().getScaledInstance(30, 30, Image.SCALE_SMOOTH);

    public Dandelion(Point position, World world, int age) {
        super(0, position, world, age);
    }

    @Override
    public ImageIcon getIcon() {
        return dandelionIcon;
    }

    @Override
    protected boolean canReproduceThisTurn() {
        return (Math.random() < 0.03);
    }

    @Override
    public void action() {
        int i = 0;
        while(i < 3) {
            if(canReproduceThisTurn() && hasFreeSpace() && age != 0) {
                reproduce(position);
                break;
            }
            i++;
        }
        age++;
    }
}
