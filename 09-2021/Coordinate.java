import java.util.ArrayList;
import java.util.Objects;

public record Coordinate(int x, int y) {
    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    // all possible coordinates that can be reached from the current coordinate.
    public ArrayList<Coordinate> getPossibleKnightMoves() {
        int[][] offsets = {
            {-2, -1},
            {2, -1},
            {-2, 1},
            {2, 1},
            {-1, -2},
            {1, -2},
            {-1, 2},
            {1, 2}
        };
        ArrayList<Coordinate> coordinates = new ArrayList<>();
        for (int[] offset : offsets) {
            int nx = this.x + offset[0];
            int ny = this.y + offset[1];
            if (nx < 0 || nx >= Board.SIZE || ny < 0 || ny >= Board.SIZE) continue;
            coordinates.add(new Coordinate(nx, ny));
        }
        return coordinates;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || this.getClass() != o.getClass()) return false;
        Coordinate that = (Coordinate) o;
        return x == that.x && y == that.y;
    }

    @Override
    public int hashCode() {
        return Objects.hash(x, y);
    }

    @Override
    public String toString() {
        return this.x + "," + this.y;
    }
}
