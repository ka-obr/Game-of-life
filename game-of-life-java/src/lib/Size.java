package lib;
import java.io.Serializable;

public class Size implements Serializable {
    private static final long serialVersionUID = 1L;
    public final int x;
    public final int y;

    public Size(int width, int height) {
        this.x = width;
        this.y = height;
    }

    @Override
    public int hashCode() {
        return java.util.Objects.hash(x, y);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Size other = (Size) obj;
        return this.x == other.x && this.y == other.y;
    }
}
