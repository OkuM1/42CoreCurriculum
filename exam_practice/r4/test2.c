node


int main(int ac, char **av)
{
    if (ac != 2)
    {
        return 1;
    }
    char *input = av[1];
    node *tree = parse_expr(&input);

    if (!tree)
    {
        destroy_tree(tree);
        return 1;
    }
    else if (*input)
    {
        unexpected(*input);
        destroy(tree);
        return (1);
    }
    printf("%d\n", eval_tree(tree));
    destroy_tree(tree);
    return 0;
}