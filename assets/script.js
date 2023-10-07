$('.open_button').on('click', () => {
    $('header').toggleClass('headerHidden');
});

$('.select').on('click', () => {
    let $options = $('.options');
    let $selectIcon = $('.select-icon-arrow');

    if ($options.is(':visible')) {
        $options.fadeOut('fast');
        $selectIcon.css('transform', 'rotate(180deg)');
    } else {
        $options.fadeIn('fast');
        $selectIcon.css('transform', 'rotate(0deg)');
    }
});

$(document).on('click', (event) => {
    let $options = $('.options');
    let $selectIcon = $('.select-icon-arrow');

    if (
        !$options.is(event.target) &&
        $options.has(event.target).length === 0 &&
        !$('.select').is(event.target) &&
        $('.select').has(event.target).length === 0
    ) {
        $options.fadeOut('fast');
        $selectIcon.css('transform', 'rotate(180deg)');
    }
});
