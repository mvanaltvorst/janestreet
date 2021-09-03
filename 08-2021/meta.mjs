import Game from './game.mjs';

function probabilityOneWinMC(q) {
    const N = 1e7;
    let oneWins = 0;
    for (let i = 0; i < N; i++) {
        let game = new Game(q);
        if (game.play() == 1) oneWins++;
    }
    return oneWins / N;
}

export { probabilityOneWinMC }