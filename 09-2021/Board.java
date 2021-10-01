import java.util.Arrays;
import java.util.List;

public class Board {
    static int SIZE = 10;
    static int AMOUNT_OF_PARTITIONS = 17;
    static int[][] PARTITIONS = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {0, 0, 0, 1, 0, 0, 0, 0, 2, 0 },
        {0, 0, 0, 1, 0, 0, 0, 0, 2, 0 },
        {0, 0, 1, 1, 1, 1, 3, 2, 2, 2 },
        {4, 0, 1, 0, 0, 11,3, 3, 3, 3 },
        {4, 0, 0, 0, 11,11,11,13,13,3 },
        {4, 5, 5, 16,11,12,12,13,13,10},
        {4, 6, 5, 16,16,14,14,14,13,10},
        {4, 6, 7, 16,15,15,15,9, 9, 10},
        {6, 6, 7, 8, 8, 8, 8, 8, 9, 10},
    };
    static List<Integer> KNIGHTS_ALREADY_PLACED = Arrays.asList(
        2, 5, 8, 12, 14, 20, 23, 28, 33
    );
    private final int[][] values;
    private final int currentKnight;

    public Board() {
        // -1: not yet filled
        this.values = new int[][]{
            {12,-1,-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1, 5,-1,23,-1},
            {-1,-1,-1,-1,-1,-1, 8,-1,-1,-1},
            { 1,-1,-1,14,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
            {-1, 2,-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,20,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,33,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,28}
        };
        this.currentKnight = 1;
    }

    public Board(int[][] values, int currentKnight) {
        this.currentKnight = currentKnight;
        this.values = values;
    }

    public int getCurrentKnight() {
        return this.currentKnight;
    }

    private int[] partitionSums() {
        int[] sums = new int[AMOUNT_OF_PARTITIONS];
        for (int i = 0; i < AMOUNT_OF_PARTITIONS; i++) {
            sums[i] = 0;
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this.values[i][j] == -1) continue;
                sums[PARTITIONS[i][j]] += this.values[i][j];
            }
        }
        return sums;
    }

    public boolean isFinished() {
        return this.currentKnight >= 33 && this.allSumsEqual();
    }

    // returns whether the sum of all numbers in all partitions are equal.
    public boolean allSumsEqual() {
        int[] sums = this.partitionSums();
        int sumInSinglePartition = sums[0];
        for (int i = 1; i < AMOUNT_OF_PARTITIONS; i++) {
            if (sums[i] != sumInSinglePartition) return false;
        }
        return true;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                int value = this.values[i][j];
                if (value == -1) {
                    sb.append("#\t");
                } else {
                    sb.append(value).append('\t');
                }
            }
            sb.append('\n');
        }
        return sb.toString();
    }

    // null if not found
    public Coordinate positionOf(int knight) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this.values[i][j] == knight) {
                    return new Coordinate(j, i);
                }
            }
        }
        return null;
    }

    public Coordinate positionOfCurrentKnight() {
        Coordinate position = this.positionOf(this.currentKnight);
        if (position == null) {
            throw new IllegalStateException("current knight is not contained on board");
        } else {
            return position;
        }
    }

    public boolean positionTaken(Coordinate position) {
        return this.values[position.getY()][position.getX()] != -1;
    }

    public boolean isLegal() {
        // illegal if there exists sum of partition >= 75
        final int THRESHOLD = 75;
        int[] sums = this.partitionSums();
        for (int i = 0; i < AMOUNT_OF_PARTITIONS; i++) {
            if (sums[i] < THRESHOLD && sums[i] >= THRESHOLD - currentKnight) return false;
        }
        return true;
    }

    public Board boardWithMoveApplied(Coordinate position) {
        int[][] newValues = new int[SIZE][SIZE];
        for (int i = 0; i < SIZE; i++) {
            newValues[i] = Arrays.copyOf(this.values[i], SIZE);
        }
        int newKnight = currentKnight + 1;
        newValues[position.getY()][position.getX()] = newKnight;
        return new Board(newValues, newKnight);
    }

    public int finalAnswer() {
        int[] highestValues = new int[SIZE];
        for (int i = 0; i < SIZE; i++) {
            highestValues[i] = -1;
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (this.values[i][j] > highestValues[i]) {
                    highestValues[i] = this.values[i][j];
                }
            }
        }
        int acc = 0;
        for (int i = 0; i < SIZE; i++) {
            System.err.printf("%d:\t%d\t%d%n", i, highestValues[i], highestValues[i]*highestValues[i]);
            acc += highestValues[i]*highestValues[i];
        }
        return acc;
    }
}


