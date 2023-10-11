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

$('.copy-icon').on('click', () => {
    let text = $('.text').val().trim();
    if(text!='') {
        navigator.clipboard.writeText(text);
        $('.copy-text').fadeIn();
        setInterval(()=> {$('.copy-text').fadeOut()}, 2000)
    }
})

$(".option").on('click', (event) => {

    let target = $(event.target);
    // console.log(target.text())
    let aux = $('.select').text().trim();
    
    $('.select').html(`${target.text()}<i class="fas fa-chevron-down select-icon-arrow"></i>`);
    target.text(aux);
    

    $('.options').fadeOut('fast');
    $('.select-icon-arrow').css('transform', 'rotate(180deg)');
})