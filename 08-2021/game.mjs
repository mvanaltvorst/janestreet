export default class Game {
  constructor(flag = 0) {
    this.flag = flag;
    this.whoseTurn = 1;
  }

  play() {
    while (true) {
      if (this.whoseTurn == 1) {
        this.flag += Game.#unif();
        if (this.flag > 1/2) return 1;
      } else {
        this.flag -= Game.#unif();
        if (this.flag < -1/2) return 2;
      }
      this.whoseTurn = Game.#otherPlayer(this.whoseTurn);
    }
  }

  static #otherPlayer(currentPlayer) {
    if (currentPlayer == 1) return 2;
    else return 1;
  }

  static #unif() {
    return Math.random();
  }
}