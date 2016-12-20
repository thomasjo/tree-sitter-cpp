#include <tree_sitter/parser.h>

#define STATE_COUNT 3
#define SYMBOL_COUNT 2
#define TOKEN_COUNT 2

enum {
    sym_comment = 1,
};

static const char *ts_symbol_names[] = {
    [ts_builtin_sym_end] = "END",
    [sym_comment] = "comment",
};

static const TSSymbolMetadata ts_symbol_metadata[SYMBOL_COUNT] = {
    [ts_builtin_sym_end] = {
        .visible = false,
        .named = true,
        .structural = true,
        .extra = false,
    },
    [sym_comment] = {
        .visible = true,
        .named = true,
        .structural = true,
        .extra = true,
    },
};

static bool ts_lex(TSLexer *lexer, TSStateId state) {
    START_LEXER();
    switch (state) {
        case 0:
            if (lookahead == 0)
                ADVANCE(1);
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                SKIP(0);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        case 1:
            ACCEPT_TOKEN(ts_builtin_sym_end);
        case 2:
            if (lookahead == '*')
                ADVANCE(3);
            if (lookahead == '/')
                ADVANCE(6);
            LEX_ERROR();
        case 3:
            if (lookahead == '*')
                ADVANCE(4);
            if (!((lookahead == 0) ||
                (lookahead == '*')))
                ADVANCE(3);
            LEX_ERROR();
        case 4:
            if (lookahead == '/')
                ADVANCE(5);
            if (!((lookahead == 0) ||
                (lookahead == '/')))
                ADVANCE(3);
            LEX_ERROR();
        case 5:
            ACCEPT_TOKEN(sym_comment);
        case 6:
            if (!((lookahead == 0) ||
                (lookahead == '\n')))
                ADVANCE(6);
            ACCEPT_TOKEN(sym_comment);
        case 7:
            if ((lookahead == '\t') ||
                (lookahead == '\n') ||
                (lookahead == '\r') ||
                (lookahead == ' '))
                SKIP(7);
            if (lookahead == '/')
                ADVANCE(2);
            LEX_ERROR();
        default:
            LEX_ERROR();
    }
}

static TSStateId ts_lex_states[STATE_COUNT] = {
    [0] = 0,
    [1] = 7,
    [2] = 0,
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

static unsigned short ts_parse_table[STATE_COUNT][SYMBOL_COUNT] = {
    [0] = {
        [ts_builtin_sym_end] = ACTIONS(1),
        [sym_comment] = ACTIONS(3),
    },
    [1] = {
        [sym_comment] = ACTIONS(5),
    },
    [2] = {
        [ts_builtin_sym_end] = ACTIONS(8),
        [sym_comment] = ACTIONS(3),
    },
};

static TSParseActionEntry ts_parse_actions[] = {
    [0] = {.count = 0, .reusable = false, .depends_on_lookahead = false},
    [1] = {.count = 1, .reusable = true, .depends_on_lookahead = false}, RECOVER(0),
    [3] = {.count = 1, .reusable = true, .depends_on_lookahead = true}, SHIFT_EXTRA(),
    [5] = {.count = 2, .reusable = true, .depends_on_lookahead = true}, SHIFT(2), SHIFT_EXTRA(),
    [8] = {.count = 1, .reusable = true, .depends_on_lookahead = false}, ACCEPT_INPUT(),
};

#pragma GCC diagnostic pop

EXPORT_LANGUAGE(ts_language_cpp);
