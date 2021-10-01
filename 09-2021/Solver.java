import java.util.LinkedList;
import java.util.Queue;

/*
Idea: breadth first search
Let's assume we have already found the position of '1' for simplicity.
We will enumerate all values from 1 (2, 3, 4, ....)
2 is already placed, so we continue
Now 3: there are a few possible solutions for 3
from this point on we create a tree. We will check all possible places for 3
for all these places, place a 4
for all these places, place a 5
notice that 5 has already been placed (it's a fixed)
now we will prune every possible board where the actual 5 is not equal to the imaginary 5.

we only do places which are valid: e.g. don't place a number on top of a number previously visited

if the sum of a region becomes > 75, we stop evaluating this branch any further (impossible state)
if all sums are equal, we stop (we have found the solution).
 */
public class Solver {
    public Solver() {
    }

    public Board solve() {
        Queue<Board> boards = new LinkedList<>();
        boards.add(new Board());
        Board current = null;
        while (!boards.isEmpty()) {
            current = boards.poll();
            if (current.isFinished()) break;
            Coordinate position = current.positionOfCurrentKnight();
            for (Coordinate potentialNewPosition : position.getPossibleKnightMoves()) {
                if (Board.KNIGHTS_ALREADY_PLACED.contains(current.getCurrentKnight() + 1)) {
                    // only add a new board where the new position is equal to the old position
                    Coordinate positionInActualBoard = current.positionOf(current.getCurrentKnight() + 1);
                    if (!positionInActualBoard.equals(potentialNewPosition)) {
                        continue;
                    }
                } else if (current.positionTaken(potentialNewPosition)) {
                    continue;
                }
                if (!current.isLegal()) continue;
                boards.add(current.boardWithMoveApplied(potentialNewPosition));
            }
        }
        if (!current.isFinished()) {
            System.err.println("No solution");
            return new Board();
        }
        System.err.println("Found solution:");
        System.err.println(current);
        return current;
    }
}
