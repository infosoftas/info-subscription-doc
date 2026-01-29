Example: Vipps or MobilePay as Payment Agreement
------------------------------------------------

To use Vipps or MobilePay as the payment method, set the ``paymentAgreementParameters`` as follows:

.. code-block:: json
    :caption: Vipps Payment Agreement Parameters
    :name: payment-agreement-vipps

    {
      "paymentMethod": "Vipps",
      "vippsMobilePayParameters": {
        "customerPhoneNumber": "+4791234567",
        "merchantAgreementUrl": "https://yourdomain.com/selfservice/vipps-agreement-info",
        "merchantRedirectUrl": "https://yourdomain.com/order/complete",
        "accountId": "your-account-id"
        "profileScope": "name address email"
      }
    }

- ``paymentMethod`` must be set to ``Vipps`` or ``MobilePay``.
- ``vippsMobilePayParameters`` is an object with the following fields:

  - ``customerPhoneNumber`` (optional): The phone number to pre-fill in the Vipps dialog.
  - ``merchantAgreementUrl``: URL to your self-service agreement page.
  - ``merchantRedirectUrl``: URL to redirect the user after approval/rejection in the Vipps app.
  - ``profileScope`` (optional): Setting the profile scope will ask the user to share his/her contact details such as name, address, and email.



Example: SwedbankPay as Payment Agreement
------------------------------------------

To use SwedbankPay as the payment method, set the ``paymentAgreementParameters`` as follows:

.. code-block:: json
    :caption: SwedbankPay Payment Agreement Parameters
    :name: payment-agreement-swedbankpay

    {
      "paymentMethod": "SwedbankPay",
      "payExEcommerceParameters": {
        "callbackUrl": "https://yourdomain.com/api/payment/callback",
        "cancelUrl": "https://yourdomain.com/order/cancel",
        "completeUrl": "https://yourdomain.com/order/complete",
        "payExAccountId": "your-payex-account-id",
        "culture": "nb-NO"
      }
    }

- ``paymentMethod`` must be set to ``SwedbankPay``.
- ``payExEcommerceParameters`` is an object with the following fields:
  - ``callbackUrl``: URL for payment status callbacks from SwedbankPay.
  - ``cancelUrl``: URL to redirect the user if the payment is cancelled.
  - ``completeUrl``: URL to redirect the user after successful payment.
  - ``payExAccountId`` (optional): The SwedbankPay account to use.
  - ``culture`` (optional): Language/culture code for the payment window (e.g., ``nb-NO``).

Refer to the API documentation for additional options and required fields for other payment methods.

