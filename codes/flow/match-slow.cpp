array<int, sz> match;
array<bool, sz> vis;
bool dfs(int now) {
    if(vis[now]) return false;
    vis[now] = true;
    for(int i = 0; i < n; i++) {
        if(!G[now][i]) continue;
        if(match[i] == -1 or dfs(match[i]))
            return match[i] = now, true;
    }
    return false;
}
int solve() {
    match.fill(-1);
    int r = 0;
    for(int i = 0; i < n; i++) {
        vis.fill(false);
        if(dfs(i)) r++;
    }
    return r;
}
