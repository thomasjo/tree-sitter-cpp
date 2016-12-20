const PREC = {
};

module.exports = grammar({
  name: 'cpp',

  extras: $ => [
    /\s/,
    $.comment,
  ],

  rules: {
    comment: $ => token(choice(
      seq(
        '//',
        /.*/
      ),
      seq(
        '/*',
        repeat(choice(/[^\*]/, /\*[^/]/)),
        '*/'
      )
    )),
  },
});
