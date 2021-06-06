// Pre-order traversal without recursion.
void pre_order_traversal(TreeNode *root){
    stack<TreeNode *> dfs;
    dfs.push(root);
    
    while (!dfs.empty()) {
        
        auto cur_node = dfs.top();
        dfs.pop();
        
        if (!cur_node)
            continue;
        
        cout << cur_node->val << endl;
        
        dfs.push(cur_node->right);
        dfs.push(cur_node->left);
    }
}

// In-order traversal without recursion.
void in_order_traversal(TreeNode *root){
    stack<TreeNode *> dfs;
    auto current = root;
    while (!dfs.empty() || current) {
        if (current){
            dfs.push(current);
            current = current->left;
        }
        else {
            current = dfs.top();
            dfs.pop();
            cout << current->val << endl;
            current = current->right;
        }
    }
}

// Post-order traversal without recursion.
void post_order_traversal(TreeNode *root){
    if (!root)
        return;
    
    stack<TreeNode *> dfs;
    map<TreeNode *, bool> visited;
    dfs.push(root);

    while (!dfs.empty()) {
        auto cur_node = dfs.top();
        if (visited[cur_node]){
            cout << cur_node->val << endl;
            dfs.pop();
            continue;
        }
        visited[cur_node] = true;
        if (cur_node->right)
            dfs.push(cur_node->right);
        if (cur_node->left)
            dfs.push(cur_node->left);
    }
}

// A more generic way to write all three different traversals:
// Use a map to record the number of times we've seen this node.

// pre-order traversal without recursion.
void pre_order_traversal(TreeNode *root){
    
    stack<TreeNode *> dfs;
    map<TreeNode *, int> visited;
    dfs.push(root);

    while (!dfs.empty()) {
        auto cur_node = dfs.top();
        
        if (!cur_node){
            dfs.pop();
            continue;
        }
        
        switch (++visited[cur_node]){
                
            case 1:
                cout << cur_node->val << endl;
                dfs.push(cur_node->left);
                break;
                
            case 2:
                dfs.push(cur_node->right);
                break;
                
            case 3:
                dfs.pop();
                break;
                
            default:
                break;
        }
    }
}

// In-order traversal without recursion.
void in_order_traversal(TreeNode *root){
    
    stack<TreeNode *> dfs;
    map<TreeNode *, int> visited;
    dfs.push(root);

    while (!dfs.empty()) {
        auto cur_node = dfs.top();
        
        if (!cur_node){
            dfs.pop();
            continue;
        }
        
        switch (++visited[cur_node]){
            case 1:
                dfs.push(cur_node->left);
                break;
            case 2:
                cout << cur_node->val << endl;
                dfs.push(cur_node->right);
                break;
                
            case 3:
                dfs.pop();
                break;
                
            default:
                break;
        }
    }
}

// Post-order traversal without recursion.
void post_order_traversal(TreeNode *root){
    
    stack<TreeNode *> dfs;
    map<TreeNode *, int> visited;
    dfs.push(root);

    while (!dfs.empty()) {
        auto cur_node = dfs.top();
        
        if (!cur_node){
            dfs.pop();
            continue;
        }
        
        switch (++visited[cur_node]){
            case 1:
                dfs.push(cur_node->left);
                break;
                
            case 2:
                dfs.push(cur_node->right);
                break;
                
            case 3:
                cout << cur_node->val << endl;
                dfs.pop();
                break;
                
            default:
                break;
        }
    }
}

