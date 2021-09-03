import Game from './game.mjs';
import { probabilityOneWinMC } from './meta.mjs';

for (let q = -0.5; q < -0.0; q += 0.01) {
    console.log(`${q}\t${probabilityOneWinMC(q)}`)
}
