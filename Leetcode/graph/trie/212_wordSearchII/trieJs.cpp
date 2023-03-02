/**
 * @param {character[][]} board
 * @param {string[]} words
 * @return {string[]}
 */
const endWord = '*'
class Trie {
    constructor(words) {
        this.root = {}
            this.isWord = false
            words.forEach(word = > this.addWord(word))
    }

    addWord(word) {
        let current = this.root

            for (const letter of word) {
                if (!current[letter]) {
                    current[letter] = {}
                }
                current = current[letter]
            }
        current.isWord = true
    }
}

function viewTrie(node) {
    if (node == null) {
        return
    }
    for (const child in node) {
        console.log(child)
            viewTrie(node[child])
    }
    return
}
var findWords = function(board, words) {
    const trie = new Trie(words)
        const result = new Set()
        viewTrie(trie.root)
        console.log(trie)
        const dfs = (i, j, node, subResult, visited) = > {
        //base cases: out of bounds, letter does not exist in next prefix
         //console.log(i+" " + j ) 
        if (i < 0 || i >= board.length || j < 0 || j >= board[0].length || !node[board[i][j]] || visited[i][j]) {
            return
        }
        visited[i][j] = 1;
        subResult += board[i][j]
            node = node[board[i][j]]
            if (node.isWord) {
                result.add(subResult)
            }
        dfs(i, j + 1, node, subResult, visited)
            dfs(i, j - 1, node, subResult, visited)
            dfs(i - 1, j, node, subResult, visited)
            dfs(i + 1, j, node, subResult, visited)
            visited[i][j] = 0;

    }

    for (let i = 0; i < board.length; i++) {
        for (let j = 0; j < board[0].length; j++) {
            let visited = new Array()
                for (let k = 0; k < board.length; k++) {
                    let v = new Array();
                    for (let p = 0; p < board[0].length; p++) {
                        v.push(0);
                    }
                    visited.push(v)
                }
            if (trie.root[board[i][j]]) {
                //console.log(i+" checking " + j)
                dfs(i, j, trie.root, "", visited)
            }
        }

    }
    return[...result]
};