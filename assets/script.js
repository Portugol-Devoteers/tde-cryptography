$(document).ready(() => {
    $('.select').data(
        'action',
        $('.select').text().trim() == 'criptografar' ? 1 : -1
    );
});

$('form').on('submit', (e) => {
    e.preventDefault();
    const text = $('.text').val().trim();
    const key = $('.key').val().trim();
    const action = $('.select').data('action');

    if (text == '' || key == '') {
        $('.status').fadeIn();
    } else {
        $('.status').fadeOut();
        $('.run-button').prop('disabled', true);
        $('.run-button').html(`
            <span class="spinner-border spinner-border-sm" role="status" aria-hidden="true"></span>                
            `);
        const request = $.ajax({
            url: 'aes-alg/API.php',
            async: true,
            type: 'POST',
            data: `text=${text}&key=${key}&action=${action}`,
            dataType: 'json',
        })
            .done((response) => {
                // console.log(response.output);
                $('.text').val(response.output);
                $('.run-button').prop('disabled', false);
                $('.run-button').html('Run');
            })
            .fail(function (jqXHR, textStatus) {
                console.log('Request failed: ' + textStatus);
                $('.run-button').prop('disabled', false);
                $('.run-button').html('Run');
                // alert('Ocorreu um erro!');
            });
    }
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
    if (text != '') {
        navigator.clipboard.writeText(text);
        $('.copy-text').fadeIn();
        setInterval(() => {
            $('.copy-text').fadeOut();
        }, 2000);
    }
});

$('.option').on('click', (event) => {
    let target = $(event.target);
    // console.log(target.text())
    let aux = $('.select').text().trim();

    $('.select').html(
        `${target.text()}<i class="fas fa-chevron-down select-icon-arrow"></i>`
    );
    target.text(aux);

    $('.select').data(
        'action',
        $('.select').text().trim() == 'criptografar' ? 1 : -1
    );

    $('.options').fadeOut('fast');
    $('.select-icon-arrow').css('transform', 'rotate(180deg)');
});
